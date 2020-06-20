using LinearAlgebra
Base.include(Main, "test.jl")
using Main.hamid
#p=llaToEcef(10,10,10)

# state : position  velocity attitude , gyro bias, accell bias

# input are :
#acceleration from imu 3  ==> vel 3 ==> pos 3
# gps position 3
# gps velocity ?

# all the functions :



# //////////////////////////////////////////////////////////////    Function section    //////////////////////////////////////////////////////////////////////

# this function make cross product matrix
function crossM(x)
        out = [
               0 -x[3] x[2]
               x[3] 0 -x[1]
               -x[2] x[1] 0
        ]
        return out
end

function quatConj(q)

        conj = [q(1); -q(2:4)]
        return conj
end

function quatMult(q, p)
#quatMult Multiplies quaternions such that qOut = q * p

        qOut = [
                q(1) * p(1) - transpose(q(2:4)) * p(2:4)
                q(1) * p(2:4) + p(1) * q(2:4) + cross(q(2:4), p(2:4))
        ]
        return qOut
end



function quatRot(q, vec)
        #quatRot Rotates vec by quaternion q according to rotVec = q * v * q^-1

        qVec = [0; vec]
        qConj = quatConj(q)

        # q1 = quatMult(q,qVec);
        # rVec = quatMult(q1,qConj);
        # rotatedVec = rVec(2:4,1);

        # implements rotVec = q^-1 * v * q
        q1 = quatMult(qConj, qVec)
        rVec = quatMult(q1, q)
        rotatedVec = rVec(2:4, 1)
        return rotatedVec

end

# //////////////////////////////////////////////////////////////    end off function sec    //////////////////////////////////////////////////////////////////////



# //////////////////////////////////////////////////////////////    Constants section    //////////////////////////////////////////////////////////////////////


sigmaOmega = [0.01;0.01;0.01]         #gyro uncertinty in angular velocity
sigmaA = [0.01;0.01;0.01]         # acceleration uncertinty

dt= 0.01
wx = 0
wy = 0
wz = 0
r = [100;0;0]
q = [1;0;0;0]
p = [1;1;1]
v = [2;2;2]
wB = [1;1;1]
aB = [3;3;3]


ARW_g = 0.1
BI_g =  0.1
ARW_a = 0.1
BI_a =  0.1




state = [r;v;q;wB;aB]
omega = [wx; wy; wz]
capOmegaM = [
        0 -wx -wy -wz
        wx 0 wz -wy
        wy -wz 0 wx
        wz wy -wx 0
]
capOmegaB = [
        0 -state[11] -state[12] -state[13]
        state[11] 0 state -state[12]
        state[12] -state 0 state[11]
        state state[12] -state[11] 0
]



phi=I+ ((dt/2)*(capOmegaM-capOmegaB)  # state transition from w to q
qv=q[2:end]
q1=q[1]
transition = [
        -qv'
        q1 * I + crossM(qv)
]

rNew=r + ( quatRot(q, v)*dt )
vNew=v + ( ( quatRot(q, a)*(a-aB) )- aG)
qNew= phi*q


#qNoise=((sigmaOmega*dt/2)^2)*[] if all axis of noise is same use this.
qNoisePross = -0.5*dt*transition*sigmaOmega
qCov=qNoise_root*transpose(qNoise_root)

vNoisePross = quatRot(q, sigmaA)*dt
vCov = vNoisePross*transpose(vNoisePross)

rNoisePross = quatRot(q, sigmaA)*dt^2
rCov = rNoisePross*transpose(rNoisePross)

sigmaGyroDriftDot = (2*pi* BI_g^2) /log(2)/ ARW_g
biassGyroNoisePross = ((sigmaGyroDriftDot*sqrt(dt))*sqrt(dt))*I(3)
biassGyroCov =biassGyroNoisePross*transpose(biassGyroNoisePross)


sigmaAccDriftDot = (2*pi* BI_a^2) /log(2)/ ARW_a
biassAccNoisePross = ((sigmaAccDriftDot*sqrt(dt))*sqrt(dt))*I(3)
biassAccCov =biassAccNoisePross*transpose(biassAccNoisePross)

Qf = []

pVpQ = 2* Qf [0 transpose(a)
                a   -crossM(a)]

F = I + [
     zeros(3,3) I(3) zeros(3,3) zeros(3,3)
     zeros(3,3) zeros(3,3) pVpQ zeros(3,3) -n2B
     zeros(4,3) zeros(4,3) 0.5 * capOmegaM -0.5 * transition zeros(4,3)
     zeros(3,3) zeros(3,3) zeros(3,4) zeros(3,3) zeros(3,3)
     zeros(3,3) zeros(3,3) zeros(3,4) zeros(3,3) zeros(3,3)
]
F[2:]
