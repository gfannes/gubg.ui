require(File.join(ENV['gubg'], 'shared'))
include GUBG
require('gubg/build/Executable')

task :default => :help
task :help do
    puts("The following tasks can be specified:")
    puts("* declare: SFML and local headers")
    puts("* define:")
end

task :declare do
    build_ok_fn = 'gubg.build.ok'
    Dir.chdir(shared_dir('extern')) do
        git_clone('https://github.com/SFML', 'SFML') do
            Dir.mkdir('build') unless File.exist?('build')
            Dir.chdir('build') do
                if !File.exist?(build_ok_fn)
                    #For ubuntu, these packages should be installed:
                    #sudo apt-get install freeglut3
                    #sudo apt-get install freeglut3-dev
                    #sudo apt-get install libxcb-image0
                    #sudo apt-get install libxcb-image0-dev
                    #sudo apt-get install libudev-dev
                    #sudo apt-get install libjpeg-dev
                    #sudo apt-get install libopenal-dev
                    #sudo apt-get install libvorbis-dev
                    #sudo apt-get install libflac-dev
                    sh 'cmake .. -DBUILD_SHARED_LIBS=FALSE'
                    sh 'make -j 4'
                    sh "touch #{build_ok_fn}"
                end
            end
            publish('build/lib', pattern: '*.a', dst: 'lib'){|fn|fn.gsub(/-s\.a$/, '.a')}
            # publish('build/lib', pattern: '*.a', dst: 'lib')
            publish('include', pattern: '**/*', dst: 'include')
        end if os == :linux
    end
    publish('fonts', dst: 'fonts')
end

task :define => :declare do
    publish('src', pattern: '**/*.hpp', dst: 'include')
end

task :test do
    exe = Build::Executable.new('test.exe')
    exe.set_cache_dir('.cache')
    exe.add_include_path(shared_dir('include'))
    exe.add_sources('src/test/test.cpp')
    exe.add_library_path(shared_dir('lib'))
    sfml_libs = %w[window graphics audio network system].map{|n|"sfml-#{n}"}
    exe.add_library(sfml_libs)
    exe.add_library(%w[xcb xcb-randr xcb-image udev jpeg GL GLU X11 X11-xcb pthread openal freetype])
    exe.run
end
