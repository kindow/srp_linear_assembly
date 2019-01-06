################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Dilation.obj: ../Dilation.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="Dilation.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Edge_Histogram.obj: ../Edge_Histogram.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="Edge_Histogram.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

NCC_all_orin.obj: ../NCC_all_orin.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="NCC_all_orin.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

NCC_sa_all.obj: ../NCC_sa_all.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="NCC_sa_all.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

NCC_sa_last_line.obj: ../NCC_sa_last_line.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="NCC_sa_last_line.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Stereo_Vision_sa.obj: ../Stereo_Vision_sa.sa $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="Stereo_Vision_sa.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/bin/cl6x" -mv6600 --abi=eabi -O2 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0/include" --diag_warning=225 --diag_wrap=off --display_error_number --openmp --preproc_with_compile --preproc_dependency="main.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/linker.cmd: ../omp_config.cfg
	@echo 'Building file: $<'
	@echo 'Invoking: XDCtools'
	"C:/ti/xdctools_3_25_04_88/xs" --xdcpath="C:/ti/omp_1_02_00_05/packages;C:/ti/bios_6_35_04_50/packages;C:/ti/ipc_1_24_03_32/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/uia_1_02_00_07/packages;C:/ti/mcsdk_2_01_02_06/demos;C:/ti/ccsv6/ccs_base;" xdc.tools.configuro -o configPkg -t ti.targets.elf.C66 -p ti.omp.examples.platforms.evm6678 -r debug -c "C:/ti/ccsv6/tools/compiler/ti-cgt-c6000_8.1.0" "$<"
	@echo 'Finished building: $<'
	@echo ' '

configPkg/compiler.opt: | configPkg/linker.cmd
configPkg/: | configPkg/linker.cmd


