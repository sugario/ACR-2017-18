# *SETUP USING VCPKG*
#### Prerequisite:
 1) Latest [CUDA 9.2](https://developer.nvidia.com/cuda-downloads?target_os=Windows&target_arch=x86_64&target_version=10) installed
 2) Visual Studio 2015 (or VS 2017 with toolkit v140 installed; VS 2017 toolkit v141 not supported by CUDA)
#### Pre-steps (get fresh vcpkg):
>cd ACR-2017-18/Seminar_3/*

>git clone https://github.com/Microsoft/vcpkg

>cd vcpkg

>bootstrap-vcpkg.bat
#### Setup:
>go to vcpkg/triplets and edit **x64-windows.cmake**.

>Add ***"set(VCPKG_PLATFORM_TOOLSET v140)"*** at the end.

>This is needed for CUDA since it does not support latest VS toolset v141 (VS 2017)

In cmd (inside folder vcpkg):
>vcpkg install opencv[cuda]:x64-windows

>vcpkg export opencv:x64-windows cuda:x64-windows --nuget

*When done, output will be something like:*

	NuGet package exported at: D:/repo/ACR-2017-18/Seminar_3/vcpkg/vcpkg-export-20180603-230557.nupkg
*Note that you only need to do this once, unless deleted. Just remember the name.*

*With a project open, go to Tools->NuGet Package Manager->Package Manager Console and paste:*

	Install-Package vcpkg-export-20180603-230557 -Source "D:\repo\ACR-2017-18\Seminar_3\vcpkg"
