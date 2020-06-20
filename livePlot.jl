function livePlot(fIn,numPlot,plotTime,row)
    if watch_file(fIn, 10).changed == 1
        windSec = plotTime # window x axis range
        readData = readdlm(fIn, ',', Float64) # rading the txt file
        data =Node([zeros(windSec-1) ; readData[1,row]] ) # rading the txt file

        datat=Node([zeros(windSec-1) ; readData[1,1]] ) #test

        initLeng=length(to_value(data))

        t = lift(b -> length(b), data)
        tt = lift(b -> length(b), datat) #test

        print("fucking t is " , t , "\n")
        y = lift(a -> to_value(data)[max(1, a-initLeng+1):max(a,initLeng)], t)

        #x = lift(c -> collect(max(c-initLeng+1, 1):max(c, initLeng)), t)
        x= 1:initLeng
        x= collect(x)*0.1

        x=lift(a -> to_value(datat)[max(1, a-initLeng+1):max(a,initLeng)], tt) #test
        scene = Scene()
        lines!(scene, x, y)
        display(scene)
        while true && isopen(scene)
            if watch_file(fIn, 3).changed == 1
                try
                    readData = readdlm(fIn, ',', Float64)
                catch e

                end
                #push!(data, append!(to_value(data), readData[1,2]))
                data[] = append!(to_value(data), readData[1,2])
                datat[] = append!(to_value(datat), readData[1,1])#test
                AbstractPlotting.update!(scene)
                #AbstractPlotting.update_limits!(scene)
            end
        end
    end
end

cd("F:\\projectDrone\\PrjectDrone\\shared")
using DelimitedFiles
using Makie
using  FileWatching
livePlot("readMe.txt",0,200,2)
