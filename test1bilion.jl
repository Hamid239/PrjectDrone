function makie_live(;

            # do the loop
            dt =0.01
            frame_start = 0
            frame_time = [0,0.1,0.6]
            aframe = frame_time.*dt
            scene = lines(frame_start .+ frame_time, aframe)
            display(scene)
            lineplot = scene[end]
            fix = 0
            i = 0
            while isopen(scene) && i < 50 # dont loop longer than 50x for testing
                aframe .= sin.(2*pi*f0.*(frame_start .+ frame_time))
                # append!(aframe, randn(nhop)); deleteat!(aframe, 1:nhop)
                lineplot[1] = frame_start .+ frame_time
                lineplot[2] = aframe
                AbstractPlotting.update_limits!(scene)
                AbstractPlotting.update!(scene)
                sleep(hopsec)
                frame_start += hopsec
            end # while loop
            scene
        end
        makie_live()
