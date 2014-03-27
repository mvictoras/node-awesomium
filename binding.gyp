{
	'targets': [{
		'target_name': 'awesomium',
        'variables': {
            'WIN_LIBJPEG_ROOT%': 'C:\\libjpeg-turbo\\lib\\',
        },
		'default_configuration': 'Release',
        'conditions': [
            ['OS=="linux"', 
                {
		           'sources': [ 'src/awesomium.cc', 'src/webBrowser.cc', 'src/cefHandler.cc' ],
                   'include_dirs': [
                        '$(CEF3_DIR)',
                    ],
                    'defines': [
                        'USING_CEF_SHARED'
                    ],
                    'cflags_cc': [
                        '<!@(pkg-config --cflags gtk+-2.0)',
                    ],
                    'ldflags': [
                        '<!@(pkg-config --libs-only-L --libs-only-other gtk+-2.0 gthread-2.0)',
                        '-Wl,-rpath,$(CEF3_DIR)/out/Release'
                    ],
                    'libraries': [
                        '-ljpeg',
                        '<!@(pkg-config --libs-only-l gtk+-2.0 gthread-2.0)',
                        '-L$(CEF3_DIR)/out/Release',
                        '-lcef',
                        '$(CEF3_DIR)/out/Release/obj.target/libcef_dll_wrapper.a',
                    ],
                    'cflags': [
                        '-fopenmp'
                    ],
                },
            ],
            ['OS=="mac"',
                {
                   'sources': [ 'src/awesomium.cc', 'src/webBrowser.cc', 'src/cefHandler.cc' ],
                   'include_dirs': [
                        '$(CEF3_DIR)',
                    ],
                    'defines': [
                        'USING_CEF_SHARED'
                    ],
                    'cflags_cc': [
                    ],
                    'ldflags': [
                        '-Wl,-rpath,$(CEF3_DIR)/Release',
                    ],
                    'libraries': [
                        '-ljpeg',
                        '-lplugin_carbon_interpose',
                        '-L$(CEF3_DIR)/Release',
                        '-F$(CEF3_DIR)/Release',
                        '-framework', 'Chromium\ Embedded\ Framework',
                    ],
                    "xcode_settings": {
                        "OTHER_LDFLAGS": [
                            "-Wl,-install_name,@loader_path/..$(CEF3_DIR)/Release/Chromium\ Embedded\ Framework.framework"
                        ]
                    },
                    'copies': [
                        {
                            # Add library dependencies to the bundle.
                            'destination': '<(PRODUCT_DIR)',
                            'files': [
                                '$(CEF3_DIR)/Release/Chromium Embedded Framework.framework/Chromium Embedded Framework',
                                '$(CEF3_DIR)/Release/libplugin_carbon_interpose.dylib',
                            ],
                        },
                    ],
                    'postbuilds': [
                        {
                            # The framework defines its load-time path
                            # (DYLIB_INSTALL_NAME_BASE) relative to the main executable
                            # (chrome).  A different relative path needs to be used in
                            # libplugin_carbon_interpose.dylib.
                            'postbuild_name': 'Fix Framework Link of .node file',
                            'action': [
                                'install_name_tool',
                                '-change',
                                '@executable_path/Chromium Embedded Framework',
                                '${BUILT_PRODUCTS_DIR}/Chromium Embedded Framework',
                                '${BUILT_PRODUCTS_DIR}/${EXECUTABLE_PATH}'
                            ],
                        },
                        {
                            'postbuild_name': 'Fix libplugin_carbon_interpose Link of .node file',
                            'action': [
                                'install_name_tool',
                                '-change',
                                '/usr/local/lib/libplugin_carbon_interpose.dylib',
                                '${BUILT_PRODUCTS_DIR}/libplugin_carbon_interpose.dylib',
                                '${BUILT_PRODUCTS_DIR}/${EXECUTABLE_PATH}'
                            ],
                        },
                        {
                            'postbuild_name': 'Fix Framework Link (libplugin_carbon_interpose.dylib)',
                            'action': [
                                'install_name_tool',
                                '-change',
                                '@executable_path/../../../../Frameworks/Chromium Embedded Framework.framework/Chromium Embedded Framework',
                                '${BUILT_PRODUCTS_DIR}/Chromium Embedded Framework',
                                '${BUILT_PRODUCTS_DIR}/libplugin_carbon_interpose.dylib'
                            ],
                        },
                        {
                            'postbuild_name': 'Fix libplugin_carbon_interpose Link of libplugin_carbon_interpose.dylib file',
                            'action': [
                                'install_name_tool',
                                '-change',
                                '/usr/local/lib/libplugin_carbon_interpose.dylib',
                                '${BUILT_PRODUCTS_DIR}/libplugin_carbon_interpose.dylib',
                                '${BUILT_PRODUCTS_DIR}/libplugin_carbon_interpose.dylib'
                            ],
                        },
                    ],
                    'cflags': [
                        '-fopenmp'
                    ],
                },
            ],
		    ['OS=="win"',
                {
                    'link_settings': {
                        'libraries': [
                            '-l<(WIN_LIBJPEG_ROOT)turbojpeg-static.lib',
                            '-l$(AWE_DIR)build\\lib\\awesomium.lib'
                        ],
                    },
                    'include_dirs': [
                      '$(AWE_DIR)include',
                      'C:\\libjpeg-turbo\\include',
                      ],
                },
            ],
        ]
	}]
}
