using Makie

scene = Scene()
data =rand(10)

t =length(data)

x = 1:10

lines!(scene, x, data)

push!(data, append!(data, rand(10)))
