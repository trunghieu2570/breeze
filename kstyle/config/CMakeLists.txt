### configuration plugin
add_definitions(-DTRANSLATION_DOMAIN=\"coldly_style_config\")
set(kstyle_coldly_config_PART_SRCS breezestyleconfig.cpp)

set(kstyle_coldly_config_PART_SRCS ${kstyle_coldly_config_PART_SRCS} breezestyleconfigmodule.cpp)

kconfig_add_kcfg_files(kstyle_coldly_config_PART_SRCS ../breezestyleconfigdata.kcfgc)
set(kstyle_coldly_config_PART_FORMS ui/breezestyleconfig.ui)
ki18n_wrap_ui(kstyle_coldly_config_PART_FORMS_HEADERS ${kstyle_coldly_config_PART_FORMS})

kcoreaddons_add_plugin(coldlystyleconfig SOURCES
    ${kstyle_coldly_config_PART_SRCS}
    ${kstyle_coldly_config_PART_FORMS_HEADERS}
    INSTALL_NAMESPACE "kstyle_config"
)

target_link_libraries(coldlystyleconfig
    PUBLIC
        Qt6::Core
        Qt6::Gui
        Qt6::Widgets
)

if(HAVE_QTDBUS)
    target_link_libraries(coldlystyleconfig
        PUBLIC
            Qt6::DBus
    )
endif()

target_link_libraries(coldlystyleconfig
    PUBLIC
        KF6::CoreAddons
        KF6::ConfigCore
        KF6::ConfigWidgets
        KF6::I18n
)
if(QT_MAJOR_VERSION STREQUAL "6")
    target_link_libraries(coldlystyleconfig
        PUBLIC
    KF6::KCMUtils
)
endif()
kcmutils_generate_desktop_file(coldlystyleconfig)

set(coldly_settings_SOURCES main.cpp)
add_executable(coldly-settings ${coldly_settings_SOURCES} )
target_link_libraries(coldly-settings Qt6::Core Qt6::Gui Qt6::Widgets )
target_link_libraries(coldly-settings KF6::I18n KF6::KCMUtils KF6::CoreAddons)

set_target_properties(coldly-settings PROPERTIES OUTPUT_NAME coldly-settings6)

install(TARGETS coldly-settings ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

# icon: reuse breeze-settings from the system Breeze package for now

# kcmshell6 < 6.27.0 doesn't know the --smoke-test param, so skip this test for
# now.
# TODO: Drop this when KF6_MIN_VERSION >= 6.27.0
if(KF6KCMUtils_VERSION VERSION_GREATER_EQUAL "6.27.0")
    add_test(NAME coldlystyleconfig_smoketest COMMAND kcmshell6 -style Coldly --smoke-test kstyle_config/coldlystyleconfig)
    set_tests_properties(coldlystyleconfig_smoketest PROPERTIES
        ENVIRONMENT_MODIFICATION QT_PLUGIN_PATH=path_list_prepend:${CMAKE_BINARY_DIR}/bin
    )
endif()
