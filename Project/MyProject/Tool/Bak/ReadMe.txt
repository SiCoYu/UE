How to unpack and repack Unreal Engine 4 files
https://gbatemp.net/threads/how-to-unpack-and-repack-unreal-engine-4-files.531784/

================
==========
UE4 Pak 相关知识总结 
https://arcecho.github.io/2017/07/02/UE4-Pak-%E7%9B%B8%E5%85%B3%E7%9F%A5%E8%AF%86%E6%80%BB%E7%BB%93/


ArcEcho/TestPak
https://github.com/ArcEcho/TestPak

制作pak文件的一个小技巧

UE4提供了命令行工具来生成pak文件，我们只需要编写一些脚本，就可以方便按照自己的需求来生成相应的pak文件。这里说的小技巧可以让你把某个路径下的制作成pak文件时保留你想要的部分路径。具体的脚本代码如下：

# This function accepts a short package filepath with out extension.
# And when generating pak file, it will add a dummy file to the reponse file list,
# in this way, the relative path to expected package root path will be saved in pak file.
# For example:
# If the input parameters targetPackagePathRootDir="F:\\AAA\\BBB\\" assetPackage="F:\\AAA\\BBB\\CCC\\*.*",
# then in the output pak file, the file's saved path will start with "\\CCC\\"
def GenerateSplitedPaks(outputPakFileDir, targetPackagePathRootDir, assetPackage):
    pakCmdTemplate = '"{}" "{}" {} "{}"'
    urealPakToolPath = GetUnrealPakToolPath()

    outputPakFileDir = os.path.normpath(outputPakFileDir)
    targetPackagePathRootDir = os.path.normpath(targetPackagePathRootDir)
    
    filesToWrite = ""
    for associatedFile in assetPackage.associatedFiles:
        filesToWrite += ' "{}"'.format(associatedFile)  
    
    #Use hash
    pakFilename = str(hash(assetPackage.name))

    # _, pakFilename = os.path.split(assetPackage.name)
    
    outputPakFilePath = os.path.join(outputPakFileDir, pakFilename + ".pak")
    dummyPackagePath = os.path.join(targetPackagePathRootDir, "dummy.uasset")

    pakCmd = pakCmdTemplate.format(urealPakToolPath, outputPakFilePath, filesToWrite, dummyPackagePath)

    subprocess.call(pakCmd, shell=True)





























