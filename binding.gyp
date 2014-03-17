{
	'targets': [{
		'target_name': 'awesomium',
		"sources": [ "src/awesomium.cc", "src/webBrowser.cc" ],
		'default_configuration': 'Release',
        'conditions': [
            ['OS=="linux"', 
                {
                    'libraries': [
                        '-lawesomium-1-7',
                        '-ljpeg',
                    ],
                    'cflags': [
                        '-fopenmp'
                    ],
                },
            ],
            ['OS=="mac"',
                {
                    'ldflags': [
                        '-framework Awesomium',
                        '-lawesomium',
                    ],
                },
            ],
		    ['OS=="win"',
                {
                    'libraries': [
                        '-l"C:\libjpeg-turbo64\lib\turbojpeg.lib"',
                        '-lawesomium',
                        '-L${AWE_DIR)build/lib'
                    ],
                    'include_dirs': [
                      '$(AWE_DIR)include',
                      'C:\libjpeg-turbo64\include',
                      ],
                },
            ],
        ]
	}]
}
