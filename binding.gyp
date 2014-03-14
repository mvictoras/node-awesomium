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
                    'ldflags': [
                        '',
                    ],
                    'include_dirs': [
                      '$(AWE_DIR)include',
                      ],
                },
            ],
        ]
	}]
}
