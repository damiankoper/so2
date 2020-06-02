mpk_sim:
	mkdir -p build && cd build && cmake .. && make -j 8

clean:
	find build ! -name '.gitkeep' -type f -exec rm {} +
	rm -rf build/CMakeFiles
	rm -rf build/MPK_Sim_autogen
