# PKG rquired :
# HDF5
#CSV , DataFrames , stdlib
#using CSV
#using DataFrames
using DelimitedFiles

cd("F:\\projectDrone\\PrjectDrone")
t = collect(0:0.05:200)
position=sin.(t)
position2=(t).^2
position3=-(t).^2
open("delim_file.txt", "a") do io
           writedlm(io,["NAME" "time"],',')
       end



for i in 2:length(t)
    print(" i is= ",i)
    println()
    open("delim_file.txt", "a") do io
              writedlm(io,[t[i] position[i] position2[i] position3[i]],',')

    end
    open("readMe.txt", "w") do io
              writedlm(io,[t[i] position[i] position2[i] position3[i] ],',')
              # b=[t[i] position[i]]
              # a=[t[i-1] position[i-1]]
              # c= [a;b]
              # writedlm(io,c,',')
    end
    #sleep(0.01)
end
#
# windSec = 20
#
# readD = readdlm("writef.txt", ',', Float64)
# data =Node([zeros(windSec-1) ; readD[1,2]] )
#
# initLeng=length(to_value(data))
# tim = Node([0.01])
#
# t = lift(b -> length(b), data)
# y = lift(a -> to_value(data)[max(1, a-initLeng+1):max(a,initLeng)], t)
#
# #x = lift(c -> collect(max(c-initLeng+1, 1):max(c, initLeng)), t)
# x= 1:initLeng
#
# scene = Scene()
# lines!(scene, x, y)
#
# while true
#     if watch_file("writef.txt", -1).changed == 1
#         push!(data, append!(to_value(data), readD[1,2]))
#     end
# end
