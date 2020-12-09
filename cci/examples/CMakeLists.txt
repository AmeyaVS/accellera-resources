cmake_minimum_required(VERSION 3.8)

project(examples CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(CTest)

set(COMMON_INCLUDE "common/inc")
set(CCI_SRC "../src")

include_directories(
    ${COMMON_INCLUDE}
    ${CCI_SRC}
    $ENV{SYSTEMC_HOME}/include
    $ENV{BOOST_ROOT}
)

link_libraries(
    cciapi
    systemc
)

add_executable(
    ex01_Simple_Int_Param
    ex01_Simple_Int_Param/ex01_Simple_Int_Param.cpp
)
add_executable(
    ex02_Fully_Supported_Data_Type_Param
    ex02_Fully_Supported_Data_Type_Param/ex02_Fully_Supported_Data_Type_Param.cpp
)
add_executable(
    ex03_Elab_Time_Param
    ex03_Elab_Time_Param/ex03_Elab_Time_Param.cpp
)
add_executable(
    ex04_Simple_Immutable_Param
    ex04_Simple_Immutable_Param/ex04_Simple_Immutable_Param.cpp
)
add_executable(
    ex05_Default_and_Preset_Value
    ex05_Default_and_Preset_Value/ex05_Default_and_Preset_Value.cpp
)
add_executable(
    ex06_Parameter_Naming
    ex06_Parameter_Naming/ex06_Parameter_Naming.cpp
)
add_executable(
    ex07_Parameter_Information
    ex07_Parameter_Information/ex07_Parameter_Information.cpp
)
add_executable(
    ex08_Parameter_Value_Change_Callbacks
    ex08_Parameter_Value_Change_Callbacks/ex08_Parameter_Value_Change_Callbacks.cpp
)
add_executable(
    ex09_Parent_Control_of_Preset_Values
    ex09_Parent_Control_of_Preset_Values/ex09_Parent_Control_of_Preset_Values.cpp
)
add_executable(
    ex10_Shared_Parameters
    ex10_Shared_Parameters/ex10_Shared_Parameters.cpp
)
add_executable(
    ex11_Directly_Associating_Parameters
    ex11_Directly_Associating_Parameters/ex11_Directly_Associating_Parameters.cpp
)
add_executable(
    ex12_Indirectly_Associating_Parameters
    ex12_Indirectly_Associating_Parameters/ex12_Indirectly_Associating_Parameters.cpp
)
add_executable(
    ex13_Parameter_Value_Locking
    ex13_Parameter_Value_Locking/ex13_Parameter_Value_Locking.cpp
)
add_executable(
    ex14_Hiding_Parameters
    ex14_Hiding_Parameters/ex14_Hiding_Parameters.cpp
)
add_executable(
    ex15_Inter_Parameter_Value_Constraints
    ex15_Inter_Parameter_Value_Constraints/ex15_Inter_Parameter_Value_Constraints.cpp
)
add_executable(
    ex16_User_Defined_Data_Type
    ex16_User_Defined_Data_Type/ex16_User_Defined_Data_Type.cpp
)
add_executable(
    ex17_Preset_Values_from_Config_File
    ex17_Preset_Values_from_Config_File/ex17_Preset_Values_from_Config_File.cpp
)
add_executable(
    ex18_Preset_Values_Superset
    ex18_Preset_Values_Superset/ex18_Preset_Values_Superset.cpp
)
add_executable(
    ex19_Reset_Param
    ex19_Reset_Param/ex19_Reset_Param.cpp
)
add_executable(
    ex20_Tracing_Parameter_Activity
    ex20_Tracing_Parameter_Activity/ex20_Tracing_Parameter_Activity.cpp
)
add_executable(
    ex21_Param_Destruction_Resurrection
    ex21_Param_Destruction_Resurrection/ex21_Param_Destruction_Resurrection.cpp
)
add_executable(
    ex22_Search_Predicate
    ex22_Search_Predicate/ex22_Search_Predicate.cpp
)
add_executable(
    ex23_Hierarchical_Value_Update
    ex23_Hierarchical_Value_Update/ex23_Hierarchical_Value_Update.cpp
)


add_test(
NAME ex01_Simple_Int_Param
COMMAND ex01_Simple_Int_Param
)
add_test(
NAME ex02_Fully_Supported_Data_Type_Param
COMMAND ex02_Fully_Supported_Data_Type_Param
)
add_test(
NAME ex03_Elab_Time_Param
COMMAND ex03_Elab_Time_Param
)
add_test(
NAME ex04_Simple_Immutable_Param
COMMAND ex04_Simple_Immutable_Param
)
add_test(
NAME ex05_Default_and_Preset_Value
COMMAND ex05_Default_and_Preset_Value
)
add_test(
NAME ex06_Parameter_Naming
COMMAND ex06_Parameter_Naming
)
add_test(
NAME ex07_Parameter_Information
COMMAND ex07_Parameter_Information
)
add_test(
NAME ex08_Parameter_Value_Change_Callbacks
COMMAND ex08_Parameter_Value_Change_Callbacks
)
add_test(
NAME ex09_Parent_Control_of_Preset_Values
COMMAND ex09_Parent_Control_of_Preset_Values
)
add_test(
NAME ex10_Shared_Parameters
COMMAND ex10_Shared_Parameters
)
add_test(
NAME ex11_Directly_Associating_Parameters
COMMAND ex11_Directly_Associating_Parameters
)
add_test(
NAME ex12_Indirectly_Associating_Parameters
COMMAND ex12_Indirectly_Associating_Parameters
)
add_test(
NAME ex13_Parameter_Value_Locking
COMMAND ex13_Parameter_Value_Locking
)
add_test(
NAME ex14_Hiding_Parameters
COMMAND ex14_Hiding_Parameters
)
add_test(
NAME ex15_Inter_Parameter_Value_Constraints
COMMAND ex15_Inter_Parameter_Value_Constraints
)
add_test(
NAME ex16_User_Defined_Data_Type
COMMAND ex16_User_Defined_Data_Type
)
add_test(
NAME ex17_Preset_Values_from_Config_File
COMMAND ex17_Preset_Values_from_Config_File
)
add_test(
NAME ex18_Preset_Values_Superset
COMMAND ex18_Preset_Values_Superset
)
add_test(
NAME ex19_Reset_Param
COMMAND ex19_Reset_Param
)
add_test(
NAME ex20_Tracing_Parameter_Activity
COMMAND ex20_Tracing_Parameter_Activity
)
add_test(
NAME ex21_Param_Destruction_Resurrection
COMMAND ex21_Param_Destruction_Resurrection
)
add_test(
NAME ex22_Search_Predicate
COMMAND ex22_Search_Predicate
)
add_test(
NAME ex23_Hierarchical_Value_Update
COMMAND ex23_Hierarchical_Value_Update
)
