# CMSIS Build CMakeLists generated on 2024-01-12T16:10:05

cmake_minimum_required(VERSION 3.22)

# Target options

set(TARGET SPI_LED_Driver_Project)
set(CPU Cortex-M0)
set(PRJ_DIR "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project")
set(OUT_DIR "D:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/out/SPI_LED_Driver_Project/Target_1")
set(INT_DIR "D:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/tmp/SPI_LED_Driver_Project/Target_1")
set(FPU NO_FPU)
set(SECURE Non-secure)
set(BYTE_ORDER Little-endian)
set(OPTIMIZE none)
set(DEBUG on)
set(CC_FLAGS_GLOBAL "-std=c99 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Weverything -Wno-packed -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(CXX_FLAGS_GLOBAL "-xc++ -std=c++11 -fno-rtti -funsigned-char -fshort-enums -fshort-wchar -ffunction-sections -Weverything -Wno-packed -Wno-reserved-id-macro -Wno-unused-macros -Wno-documentation-unknown-command -Wno-documentation -Wno-license-management -Wno-parentheses-equality")
set(LD_FLAGS_GLOBAL "--library_type=microlib --map --load_addr_map_info --xref --callgraph --symbols --info sizes --info totals --info unused --info veneers --strict --summary_stderr --info summarysizes")
set(LD_SCRIPT "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/SPI_LED_Driver_Project_Target_1.sct")

set(DEFINES
  MG32F02U128
  _RTE_
  __MICROLIB
)

set(INC_PATHS
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/User/Include"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/ChipInit_Wizard/MG32F02U128"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/Device/MG32F02U128"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/_Target_1"
  "C:/Users/Zero/AppData/Local/arm/packs/ARM/CMSIS/6.0.0/CMSIS/Core/Include"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/Common/Startup"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A128/Include"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A128/MG32x02z_ConfigerWizard/Include"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Include"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Sample/Driver/Include"
)

set(AS_ARM_SRC_FILES
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/Device/MG32F02U128/startup_MG32x02z.s"
)

set(CC_SRC_FILES
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_ADC_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_APB_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_APX_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_CFG_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_CM0_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_CMP_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_CSC_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_DAC_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_DMA_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_EMB_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_EXIC_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_GPIO_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_GPL_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_I2C_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_IWDT_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_MEM_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_PW_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_RST_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_RTC_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_SPI_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_SYS_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_TM_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_URT_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_USB_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z_WWDT_DRV.c"
  "C:/Users/Zero/AppData/Local/arm/packs/Megawin/CM0_DFP/4.2.0/Device/MG32x02z/MG32F02A_Driver/Source/MG32x02z__Common_DRV.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/ChipInit_Wizard/MG32F02U128/MG32x02z_CSC_Init.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/ChipInit_Wizard/MG32F02U128/MG32x02z_ChipInit.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/ChipInit_Wizard/MG32F02U128/MG32x02z_GPIO_Init.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/Device/MG32F02U128/system_MG32x02z.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/User/Source/MG32x02z_RGBTable_API.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/User/Source/MG32x02z_RGB_API.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/User/Source/MG32x02z_RGB_MBIA045_API.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/User/Source/MG32x02z_RGB_TLC5948_API.c"
  "d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/User/Source/main.c"
)

set(AS_FLAGS_d:/STM32/Test/Examples/MG32F02A128/MG32F02U128/SPI_LED_Driver_Project/RTE/Device/MG32F02U128/startup_MG32x02z.s "-masm=auto")

# Toolchain config map

set(REGISTERED_TOOLCHAIN_ROOT "c:/Users/Zero/.vcpkg/artifacts/fd3d78d7/compilers.arm.armclang/6.21.0/bin")
set(REGISTERED_TOOLCHAIN_VERSION "6.21.0")
set(TOOLCHAIN_VERSION_MIN "6.21.0")
include ("C:/Users/Zero/.vcpkg/artifacts/fd3d78d7/tools.open.cmsis.pack.cmsis.toolbox/2.2.1/etc/AC6.6.18.0.cmake")
include ("C:/Users/Zero/.vcpkg/artifacts/fd3d78d7/tools.open.cmsis.pack.cmsis.toolbox/2.2.1/etc/CMSIS-Build-Utils.cmake")

# Setup project

project(${TARGET} LANGUAGES AS_ARM C)

cbuild_get_running_toolchain(TOOLCHAIN_ROOT TOOLCHAIN_VERSION C)

# Global Flags

set(CMAKE_AS_ARM_FLAGS "${AS_ARM_CPU} ${AS_ARM_BYTE_ORDER} ${AS_ARM_DEFINES} ${AS_ARM_OPTIONS_FLAGS} ${AS_ARM_FLAGS}")
cbuild_get_system_includes(CC_SYS_INC_PATHS_LIST CC_SYS_INC_PATHS)
set(CMAKE_C_FLAGS "${CC_CPU} ${CC_BYTE_ORDER} ${CC_DEFINES} ${CC_SECURE} ${CC_OPTIONS_FLAGS} ${CC_FLAGS} ${CC_FLAGS_GLOBAL} ${CC_SYS_INC_PATHS}")
set(CMAKE_C_LINK_FLAGS "${LD_CPU} ${_LS}\"${LD_SCRIPT}\" ${LD_SECURE} ${LD_FLAGS_GLOBAL} ${LD_OPTIONS_FLAGS} ${LD_FLAGS}")

# Local Flags

foreach(SRC ${AS_ARM_SRC_FILES})
  string(REPLACE " " "?" S ${SRC})
  if(DEFINED AS_FLAGS_${S})
    set(AS_FLAGS_LOCAL "${AS_FLAGS_${S}}")
  else()
    set(AS_FLAGS_LOCAL "${AS_FLAGS_GLOBAL}")
  endif()
  set_source_files_properties(${SRC} PROPERTIES COMPILE_FLAGS "${AS_FLAGS_LOCAL}")
  set_source_files_properties(${SRC} PROPERTIES LANGUAGE AS_ARM)
endforeach()

# Compilation Database

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_custom_target(database COMMAND ${CMAKE_COMMAND} -E copy_if_different "${INT_DIR}/compile_commands.json" "${OUT_DIR}")

# Setup Target

add_executable(${TARGET} ${AS_ARM_SRC_FILES} ${CC_SRC_FILES})
set_target_properties(${TARGET} PROPERTIES PREFIX "" SUFFIX ".axf" OUTPUT_NAME "SPI_LED_Driver_Project")
set_target_properties(${TARGET} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${OUT_DIR} LINK_DEPENDS ${LD_SCRIPT})
target_include_directories(${TARGET} PUBLIC ${INC_PATHS})
