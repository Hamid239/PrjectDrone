function work(fin,numPlot)

    ydata=Array{Observable}(undef, numPlot);
    ySize= Array{Observable}(undef,numPlot);
    y =Array{Observable}(undef,numPlot);
    scene= Array{Scene}(undef,numPlot);
    limits =Array{Observable}(undef,numPlot);
    plot = Array{Scene}(undef,numPlot);
    #cheking if my file got updated
    if  watch_file(fIn, 10).changed == 1
        plotTime= 200;# the amount of data shown on screen
        windSec = plotTime;
        initLeng= plotTime
        readData=0;
        # reading the data
        while (readData == 0)
            try
                readData = readdlm(fIn, ',', Float64)
            catch e
                readData=0;
            end
        end
        # x axis
        xdata=Node([zeros(windSec-1) ; readData[1,1]] ) ;
        xSize = lift(b -> length(b), xdata) ;
        x = lift(a -> to_value(xdata)[max(1, a-initLeng+1):max(a,initLeng)], xSize)
#=
        #Y data1 :
        ydata1=Node([zeros(windSec-1) ; readData[1,2]])
        ySize1= lift(a -> length(a), ydata1)
        y1= lift(a -> to_value(ydata1)[max(1, a-initLeng+1):max(a,initLeng)], ySize1)
        scene = Scene();
        limits1 = lift((x,y) -> FRect(to_value(x)[1], minimum(to_value(y1))-10, (to_value(x)[end]-to_value(x)[1])+5, maximum(to_value(y1))+20),x,y1)
        plot1=lines!(scene, x, y1,limits=limits1,color = :blue)
        plot1 = title(plot1, "Gx")


        #####Y data 2:
        ydata2=Node([zeros(windSec-1) ; readData[1,3]] )
        ySize2= lift(a -> length(a), ydata2)
        y2= lift(a -> to_value(ydata2)[max(1, a-initLeng+1):max(a,initLeng)], ySize2)
        scene = Scene()
        limits2 = lift((x,y) -> FRect(to_value(x)[1], minimum(to_value(y))-10, (to_value(x)[end]-to_value(x)[1])+5, maximum(to_value(y))+20),x,y2)
        plot2=lines!(scene, x, y2,limits=limits2,color = :red)
        plot2 = title(plot2, " Gy ")

=#

        for i in 1:numPlot

            ydata[i]=Node([zeros(windSec-1) ; readData[1,i+1]] )
            ySize[i]= lift(a -> length(a), ydata[i])
            y[i]= lift(a -> to_value(ydata[i])[max(1, a-initLeng+1):max(a,initLeng)], ySize[i])
            scene[i] = Scene()
            limits[i] = lift((x,y) -> FRect(to_value(x)[1], minimum(to_value(y))-10, (to_value(x)[end]-to_value(x)[1])+5, maximum(to_value(y))+20),x,y[i])
        end
        #,limits=limits[1]

        plot[1]=lines!(scene[1], x, y[1],color = :green)
        plot[2]=lines!(scene[1], x, y[2],color = :red)
        plot[3]=lines!(scene[1], x, y[3],color = :blue)
        plot[1] = title(plot[1], " accel ")

        plot[4]=lines!(scene[4], x, y[4],color = :green)
        plot[5]=lines!(scene[4], x, y[5],color = :red)
        plot[6]=lines!(scene[4], x, y[6],color = :blue)
        plot[4] = title(plot[4], " gyro ")

        plot[7]=lines!(scene[7], x, y[7],color = :green)
        plot[8]=lines!(scene[7], x, y[8],color = :red)
        plot[9]=lines!(scene[7], x, y[9],color = :blue)
        plot[7] = title(plot[7], " mag ")



        scene = AbstractPlotting.vbox(plot[1],plot[4],plot[7])

        display(scene)
        while true && isopen(scene)
            if watch_file(fIn, 10).changed == 1
                readData = 0
                while (readData==0)
                    try
                         readData = readdlm(fIn, ',', Float64)
                    catch e
                         readData=0;
                    end
                end

                #update the data :
                xdata[] = append!(to_value(xdata), readData[1,1])#test
                for i in 1:numPlot
                    ydata[i][] = append!(to_value(ydata[i]), readData[1,i+1])
                end
                #AbstractPlotting.update_limits!(scene)
                AbstractPlotting.update!(scene)

            end
        end
    end
end

cd("F:\\projectDrone\\PrjectDrone\\shared")
using DelimitedFiles
using Makie
using  FileWatching
fIn = "readMe.txt"
work(fIn,9)
