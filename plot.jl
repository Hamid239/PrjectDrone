using Makie

data = rand(100, 50)
p1 = heatmap(data, interpolate = true)
p2 = heatmap(data, interpolate = false)
scene = AbstractPlotting.vbox(p1,p2)

scene
