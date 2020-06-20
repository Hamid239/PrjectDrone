


using  FileWatching
# for i in 1:10
#     print("LOOOL ", i)
#     println()
#     sleep(1)
# end
dir=pwd()

file = joinpath(dir, "delim_file.txt")

a=wwatch_file(file, 10).changed == 1atch_file(file, 10)

if a.changed == 1
   print("niceeeeeeeeee dude ")
else
   print("shit is broken ")
end
