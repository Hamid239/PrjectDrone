function livePlot(fIn,plotTime,rowX,numPlot)

    if watch_file(fIn, 5).changed == 1
        windSec = plotTime; # window x axis range
        readData=0
        while (readData==0)
            try
                 readData = readdlm(fIn, ',', Float64)
            catch e
                 readData=0;
            end
        end
        ydata=Array{Observable}(undef, numPlot);
        initLeng=Array{Int}(undef,numPlot);
        ys= Array{Observable}(undef,numPlot);
        y =Array{Observable}(undef,numPlot);
        scene= Array{Scene}(undef,numPlot);
        sceneF= Array{Scene}(undef,numPlot);
        plot = Array{Scene}(undef,numPlot);

        xdata=Node([zeros(windSec-1) ; readData[1,rowX]] ) ;#test
        initLengX=length(to_value(xdata))
        xs = lift(b -> length(b), xdata) ;
        x = lift(a -> to_value(xdata)[max(1, a-initLengX+1):max(a,initLengX)], xs) #test

        for i in 1:numPlot
            ydata[i] =Node([zeros(windSec-1) ; readData[1,i+1]] ) # rading the txt file
            initLeng[i]=length(to_value(ydata[i]))
            ys[i] = lift(a -> length(a), ydata[i])
            y[i]= lift(a -> to_value(ydata[i])[max(1, a-initLeng[i]+1):max(a,initLeng[i])], ys[i])
            scene[i] = Scene()
            plot[i]=lines!(scene[i], x, y[i])
            #ylims!(plot[i],(0,1))
        end

    scene = AbstractPlotting.vbox(plot)
    display(scene)
    while true && isopen(scene)
        if watch_file(fIn, 5).changed == 1
            readData=0
            while (readData==0)
                try
                     readData = readdlm(fIn, ',', Float64)
                catch e
                     readData=0;
                end
            end

            #update the data :
            for i in 1:numPlot
                ydata[i][] = append!(to_value(ydata[i]), readData[1,i+1])
            end

            xdata[] = append!(to_value(xdata), readData[1,1])#test

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
livePlot("readMe.txt",200,1,3)
