require("gubg/shared")

here = File.dirname(__FILE__)

namespace :ui do
	task :prepare do
		Dir.chdir(GUBG.mkdir(here, "extern")) do
			GUBG.git_clone("https://github.com/SFML", "SFML")
			GUBG.git_clone("https://github.com/ocornut", "imgui")
			GUBG.git_clone("https://github.com/eliasdaler", "imgui-sfml")
			GUBG.git_clone('https://github.com/nsf', 'termbox')
		end
		GUBG.publish(here, 'fonts', dst: 'fonts')
		GUBG.publish(here, 'src/imui', dst: 'include/imui', pattern: '**/*.hpp')
		GUBG.publish(here, 'src/tui', dst: 'include/tui', pattern: '**/*.hpp')
		GUBG.publish(here, 'src', pattern: '**/*.hpp', dst: 'include')
	end
end