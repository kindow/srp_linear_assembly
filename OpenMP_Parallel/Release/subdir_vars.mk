################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CFG_SRCS += \
../omp_config.cfg 

SA_SRCS += \
../Dilation.sa \
../Edge_Histogram.sa \
../NCC_all_orin.sa \
../NCC_sa_all.sa \
../NCC_sa_last_line.sa \
../Stereo_Vision_sa.sa 

C_SRCS += \
../main.c 

OBJS += \
./Dilation.obj \
./Edge_Histogram.obj \
./NCC_all_orin.obj \
./NCC_sa_all.obj \
./NCC_sa_last_line.obj \
./Stereo_Vision_sa.obj \
./main.obj 

C_DEPS += \
./main.d 

GEN_MISC_DIRS += \
./configPkg/ 

GEN_CMDS += \
./configPkg/linker.cmd 

GEN_OPTS += \
./configPkg/compiler.opt 

SA_DEPS += \
./Dilation.d \
./Edge_Histogram.d \
./NCC_all_orin.d \
./NCC_sa_all.d \
./NCC_sa_last_line.d \
./Stereo_Vision_sa.d 

GEN_FILES += \
./configPkg/linker.cmd \
./configPkg/compiler.opt 

GEN_FILES__QUOTED += \
"configPkg\linker.cmd" \
"configPkg\compiler.opt" 

GEN_MISC_DIRS__QUOTED += \
"configPkg\" 

C_DEPS__QUOTED += \
"main.d" 

OBJS__QUOTED += \
"Dilation.obj" \
"Edge_Histogram.obj" \
"NCC_all_orin.obj" \
"NCC_sa_all.obj" \
"NCC_sa_last_line.obj" \
"Stereo_Vision_sa.obj" \
"main.obj" 

SA_DEPS__QUOTED += \
"Dilation.d" \
"Edge_Histogram.d" \
"NCC_all_orin.d" \
"NCC_sa_all.d" \
"NCC_sa_last_line.d" \
"Stereo_Vision_sa.d" 

SA_SRCS__QUOTED += \
"../Dilation.sa" \
"../Edge_Histogram.sa" \
"../NCC_all_orin.sa" \
"../NCC_sa_all.sa" \
"../NCC_sa_last_line.sa" \
"../Stereo_Vision_sa.sa" 

C_SRCS__QUOTED += \
"../main.c" 


