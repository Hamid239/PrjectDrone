#= start of the Kalman filter written by hamidreza ++ Rezaei
=#

## packages required for this program :
# Geodesy

module hamid
export llaToEcef

#invoking proper pkg
using Geodesy

# this function transfor LLA to ECEF

  function llaToEcef(lat,long,height)
    lla = LLA(lat, long, height)
    x_ecef = ECEF(lla, wgs84)
    return pEcef=[x_ecef.x x_ecef.y x_ecef.z]
  end
end
