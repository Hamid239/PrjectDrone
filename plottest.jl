# pkg Makie
using Makie

scene = Scene()
data = Node(zeros(1000))


t = lift(c -> length(c), data)
y = lift(a -> to_value(data)[max(1, a-999):max(a, 1000)], t)

x = lift(b -> collect(max(b-999, 1):max(b, 1000)), t)
#x = 1:1000 # for static axis
lines!(scene, x, y)


    push!(data, append!(to_value(data), rand(10)))
    #AbstractPlotting.update_limits!(scene) #comment out update calls for fixed axis
    #AbstractPlotting.update!(scene)
