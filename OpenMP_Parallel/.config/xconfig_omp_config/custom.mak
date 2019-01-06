## THIS IS A GENERATED FILE -- DO NOT EDIT
.configuro: .libraries,e66 linker.cmd package/cfg/omp_config_pe66.oe66

linker.cmd: package/cfg/omp_config_pe66.xdl
	$(SED) 's"^\"\(package/cfg/omp_config_pe66cfg.cmd\)\"$""\"C:/Users/Administrator/Desktop/msc project/ccs_program/OpenMP_Parallel/.config/xconfig_omp_config/\1\""' package/cfg/omp_config_pe66.xdl > $@
