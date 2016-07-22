require(File.join(ENV['gubg'], 'shared'))
include GUBG
require('gubg/build/Executable')
require('gubg/build/Library')

task :default => :help
task :help do
    puts("The following tasks can be specified:")
    puts("* declare: SFML and local headers")
    puts("* define:")
end

task :clean do
    rm_rf '.cache'
end

task :declare do
    build_ok_fn = 'gubg.build.ok'
    Dir.chdir(shared_dir('extern')) do
        git_clone('https://github.com/SFML', 'SFML') do
            Dir.mkdir('build') unless File.exist?('build')
            Dir.chdir('build') do
                if !File.exist?(build_ok_fn)
                    #For ubuntu, these packages should be installed:
                    #sudo apt-get install freeglut3 freeglut3-dev libxcb-image0 libxcb-image0-dev libudev-dev libjpeg-dev libopenal-dev libvorbis-dev libflac-dev libfreetype6-dev
                    sh 'cmake .. -DBUILD_SHARED_LIBS=FALSE'
                    sh 'make -j 4'
                    sh "touch #{build_ok_fn}"
                end
            end
            publish('build/lib', pattern: '*.a', dst: 'lib'){|fn|fn.gsub(/-s\.a$/, '.a')}
            # publish('build/lib', pattern: '*.a', dst: 'lib')
            publish('include', pattern: '**/*', dst: 'include')
        end if os == :linux
        git_clone('https://github.com/nsf', 'termbox') do
            if !File.exist?(build_ok_fn)
                publish('src', pattern: '*.h', dst: 'include')
                lib = Build::Library.new('termbox')
                lib.set_cache_dir('.cache')
                lib.add_include_path(shared_dir('include'))
                lib.add_sources('src/termbox.c')
                lib.add_sources('src/utf8.c')
                lib.build
                publish(lib.lib_filename, dst: 'lib')
                sh "touch #{build_ok_fn}"
            end
        end if os == :linux
    end
    publish('fonts', dst: 'fonts')
    publish('src/imui', dst: 'include/imui', pattern: '**/*.hpp')
    publish('src/tui', dst: 'include/tui', pattern: '**/*.hpp')
end

task :define => :declare do
    publish('src', pattern: '**/*.hpp', dst: 'include')
end

task :test => :declare do
    ut = Build::Executable.new('test')
    ut.set_cache_dir('.cache')
    case :debug
    when :debug
        ut.add_define('DEBUG')
        ut.add_option('g')
    end
    ut.add_include_path(shared_dir('include'))
    ut.add_sources(FileList.new('src/test/*_tests.cpp'))
    ut.add_sources(shared_file('source/catch_runner.cpp'))
    ut.add_sources(FileList.new(shared('include', '**/*.hpp')))
    ut.add_library_path(shared_dir('lib'))
    sfml_libs = %w[window graphics audio network system].map{|n|"sfml-#{n}"}
    ut.add_library(sfml_libs)
    ut.add_library(%w[xcb xcb-randr xcb-image udev jpeg GL GLU X11 X11-xcb pthread openal freetype])
    options = %w[-a -d yes]
    case :mt
    when :ut then options << '[ut]'
    when :mt then options << '[mt]'
    end
    ut.run(options)
end
