cd("F:\\projectDrone\\PrjectDrone\\shared")

fIn = "readMe.txt"
using DelimitedFiles



readData = 0
while (readData == 0)
    try
        global readData = readdlm(fIn, ',', Float64)
    catch e
        global readData=0;
    end
end

readData = 0
while (readData ==0)
    try
        global readData = readdlm(fIn, ',', Float64)
    catch e
        global readData=0;
    end
end
