project(JeanDujardin)

# Ajoute tous les fichiers source et en-tête spécifiques à la bibliothèque (de manière récursive)
file(GLOB_RECURSE JEANDUJARDIN_SOURCES
    *.cpp
    *.h
)

add_executable(JeanDujardin ${JEANDUJARDIN_SOURCES})

# Ajoute le chemin vers les entêtes
target_include_directories(JeanDujardin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/)

# Spécifie le chemin relatif du dossier 'dependances'
set(GLEW_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../dependances/glew/)

# Iinclusion de GLEW
include_directories(${GLEW_PATH}/include)

# Ajoute le répertoire où se trouvent les fichiers lib de GLEW
link_directories(${GLEW_PATH}/lib/Release/x64)

# Lier l'exécutable avec la bibliothèque GLEW
target_link_libraries(JeanDujardin PRIVATE ${GLEW_PATH}/lib/Release/x64/glew32.lib) 

# Copier les DLL de GLEW dans le répertoire de sortie après la construction
add_custom_command(TARGET JeanDujardin POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_if_different
                   ${GLEW_PATH}/bin/Release/x64/glew32.dll
                   $<TARGET_FILE_DIR:JeanDujardin>)

# Organisez l'architecture virtuelle pour refléter la structure des fichiers
foreach(_source IN ITEMS ${JEAN_SOURCES})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

########################################################################################################################
# Dépendances

########################################################################################################################
# SFML
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

target_link_libraries(JeanDujardin PRIVATE sfml-system sfml-window sfml-graphics sfml-audio sfml-network)
target_compile_features(JeanDujardin PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET JeanDujardin
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:JeanDujardin>
        VERBATIM)
endif()

install(TARGETS JeanDujardin)
########################################################################################################################

