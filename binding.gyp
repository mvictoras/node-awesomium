{
	'targets': [{
		'target_name': 'awesomium',
		"sources": [ "src/awesomium.cc", "src/webBrowser.cc" ],
		'default_configuration': 'Release',
		'xcode_settings': {
			'OTHER_CFLAGS': [
				'<!@(pkg-config --cflags poppler-glib cairo)'
			],
		},
		'cflags': [
			'<!@(pkg-config --cflags poppler-glib cairo)'
		],
		'ldflags': [
			'<!@(pkg-config --libs poppler-glib cairo)'
		],
		'libraries': [
			'<!@(pkg-config --libs poppler-glib cairo)'
		]
	}]
}
