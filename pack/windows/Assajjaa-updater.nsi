; Assajjaa.nsi

;--------------------------------

;Unicode true

XPStyle on

; The name of the installer
;Name "Assajjaa"

; The version of Assajjaa
!define Version 0.2.0


; The file to write
OutFile "Assajjaa-0.1.0to0.2.0update.exe"

; The default installation directory
;InstallDir "$PROGRAMFILES\Assajjaa"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
;InstallDirRegKey HKLM "Software\Assajjaa" "Install_Dir"


; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------
Page license
Page components
Page directory dirPre
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles
;--------------------------------

; First is default
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Arabic.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\Japanese.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\French.nlf"

; License data
LicenseLangString myLicenseData ${LANG_ENGLISH} "Assajjaa\license\en.txt"
LicenseLangString myLicenseData ${LANG_ARABIC} "Assajjaa\license\ar.txt"
LicenseLangString myLicenseData ${LANG_JAPANESE} "Assajjaa\license\ja.txt"
LicenseLangString myLicenseData ${LANG_FRENCH} "Assajjaa\license\fr.txt"
LicenseData $(myLicenseData)

; Set name using the normal interface (Name command)
LangString Name ${LANG_ENGLISH} " Assajjaa "
LangString Name ${LANG_ARABIC} " السجاع "
LangString Name ${LANG_JAPANESE} " アッサッジャア "
LangString Name ${LANG_FRENCH} " Assajjaa "
Name $(Name)

; Section Assajjaa
Section "Assajjaa"
	SectionIn RO
	
	ReadRegStr $INSTDIR HKLM "SOFTWARE\Assajjaa" "Install_Dir"

	; Set output path to the installation directory.
	SetOutPath $INSTDIR
	
	; Put file there
	File /r "Assajjaa\Assajjaa.exe"
	
	; Write the installation path into the registry
	;WriteRegStr HKLM SOFTWARE\Assajjaa "Install_Dir" "$INSTDIR"
	WriteRegStr HKLM SOFTWARE\Assajjaa "Version" "${Version}"
	
  
SectionEnd


;--------------------------------

Function .onInit
	Push ""
	Push ${LANG_ENGLISH}
	Push English
	Push ${LANG_ARABIC}
	Push Arabic
	Push ${LANG_JAPANESE}
	Push Japanese
	Push ${LANG_FRENCH}
	Push French
	Push A ; A means auto count languages
	       ; for the auto count to work the first empty push (Push "") must remain
	LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

	Pop $LANGUAGE
	StrCmp $LANGUAGE "cancel" 0 +2
		Abort
FunctionEnd

Function dirPre
	Abort
FunctionEnd