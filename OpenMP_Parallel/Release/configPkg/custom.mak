## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/omp_config_pe66.oe66

linker.cmd: package/cfg/omp_config_pe66.xdl
	$(SED) 's"^\"\(package/cfg/omp_config_pe66cfg.cmd\)\"$""\"C:/Users/Administrator/Desktop/msc project/ccs_program/openmp_debug_release_section_correct_0818/OpenMP_Parallel/Release/configPkg/\1\""' package/cfg/omp_config_pe66.xdl > $@
