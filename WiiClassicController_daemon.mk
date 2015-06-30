##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=WiiClassicController_daemon
ConfigurationName      :=Debug
WorkspacePath          := "D:\Workspaces\CodeLite\C++"
ProjectPath            := "D:\Workspaces\CodeLite\C++\WiiClassicController_daemon"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Kappa
Date                   :=30/06/2015
CodeLitePath           :="D:\Program Files\CodeLite"
LinkerName             :=K:/MinGW/bin/g++.exe
SharedObjectLinkerName :=K:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="WiiClassicController_daemon.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=K:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)vJoyInterface 
ArLibs                 :=  "vJoyInterface" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)lib 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := K:/MinGW/bin/ar.exe rcu
CXX      := K:/MinGW/bin/g++.exe
CC       := K:/MinGW/bin/gcc.exe
CXXFLAGS :=  -g -O0 -Wall -std=c++11 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall  $(Preprocessors)
ASFLAGS  := 
AS       := K:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=D:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/SerialClass.cpp$(ObjectSuffix) $(IntermediateDirectory)/JoystickHandler.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Workspaces/CodeLite/C++/WiiClassicController_daemon/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/SerialClass.cpp$(ObjectSuffix): SerialClass.cpp $(IntermediateDirectory)/SerialClass.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Workspaces/CodeLite/C++/WiiClassicController_daemon/SerialClass.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SerialClass.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/SerialClass.cpp$(DependSuffix): SerialClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/SerialClass.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/SerialClass.cpp$(DependSuffix) -MM "SerialClass.cpp"

$(IntermediateDirectory)/SerialClass.cpp$(PreprocessSuffix): SerialClass.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/SerialClass.cpp$(PreprocessSuffix) "SerialClass.cpp"

$(IntermediateDirectory)/JoystickHandler.cpp$(ObjectSuffix): JoystickHandler.cpp $(IntermediateDirectory)/JoystickHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "D:/Workspaces/CodeLite/C++/WiiClassicController_daemon/JoystickHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/JoystickHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/JoystickHandler.cpp$(DependSuffix): JoystickHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/JoystickHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/JoystickHandler.cpp$(DependSuffix) -MM "JoystickHandler.cpp"

$(IntermediateDirectory)/JoystickHandler.cpp$(PreprocessSuffix): JoystickHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/JoystickHandler.cpp$(PreprocessSuffix) "JoystickHandler.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


