; Assajjaa.nsi

;--------------------------------

;Unicode true

XPStyle on

; The name of the installer
;Name "Assajjaa"

; The file to write
OutFile "Assajjaa-0.1.0beta.exe"

; The default installation directory
InstallDir "$PROGRAMFILES\Assajjaa"

; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\Assajjaa" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------
Page license
Page components
Page directory
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
	
	; Set output path to the installation directory.
	SetOutPath $INSTDIR
	
	; Put file there
	File /r "Assajjaa\*"
	
	; Write the installation path into the registry
	WriteRegStr HKLM SOFTWARE\Assajjaa "Install_Dir" "$INSTDIR"
	
	; Write the uninstall keys for Windows
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Assajjaa" "DisplayName" "Assajjaa"
	WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Assajjaa" "UninstallString" '"$INSTDIR\uninstall.exe"'
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Assajjaa" "NoModify" 1
	WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Assajjaa" "NoRepair" 1
	WriteUninstaller "uninstall.exe"
  
SectionEnd

; Section Start Menu Shortcuts
LangString startM ${LANG_ENGLISH} "Start Menu Shortcuts"
LangString startM ${LANG_ARABIC} "اختصارات قائمة ابدأ"
LangString startM ${LANG_JAPANESE} "スタートメニューのショートカット"
LangString startM ${LANG_FRENCH} "Raccourcis du menu Démarrer"
Section !$(startM) sec1
  CreateDirectory "$SMPROGRAMS\Assajjaa"
  CreateShortCut "$SMPROGRAMS\Assajjaa\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\Assajjaa\Assajjaa.lnk" "$INSTDIR\jpconj.exe" "" "$INSTDIR\jpconj.exe" 0
SectionEnd

; Section Desktop Shortcut
LangString desk ${LANG_ENGLISH} "Desktop Shortcut"
LangString desk ${LANG_ARABIC} "اختصار سطح المكتب"
LangString desk ${LANG_JAPANESE} "デスクトップのショートカット"
LangString desk ${LANG_FRENCH} "Raccourci du bureau"
Section !$(desk) sec2
  CreateShortCut "$DESKTOP\Assajjaa.lnk" "$INSTDIR\Assajjaa.exe" "" "$INSTDIR\Assajjaa.exe" 0
SectionEnd

;--------------------------------

Function .onInit

	ReadRegStr $R0 HKLM \
	"Software\Microsoft\Windows\CurrentVersion\Uninstall\Assajjaa" \
	"UninstallString"
	StrCmp $R0 "" done
 
	MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
	"Assajjaa is already installed. $\n$\nClick `OK` to remove the \
	previous version or `Cancel` to cancel this upgrade." \
	IDOK uninst
	Abort
 
	;Run the uninstaller
	uninst:
	ClearErrors
	ExecWait '$R0 _?=$INSTDIR' ;Do not copy the uninstaller to a temp file
 
	IfErrors no_remove_uninstaller done
	;You can either use Delete /REBOOTOK in the uninstaller or add some code
    ;here to remove the uninstaller. Use a registry key to check
    ;whether the user has chosen to uninstall. If you are using an uninstaller
    ;components page, make sure all sections are uninstalled.
	no_remove_uninstaller:
	Abort
	done:

	;Language selection dialog

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

; Uninstaller

Section "Uninstall"
  
	; Remove registry keys
	DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\Assajjaa"
	DeleteRegKey HKLM SOFTWARE\Assajjaa

	; Remove files and uninstaller
	;Delete /r $INSTDIR\*
	;Delete $INSTDIR\uninstall.exe
	RMDir /r "$INSTDIR"
	
	; Remove shortcuts, if any
	Delete "$SMPROGRAMS\Assajjaa\*.*"
	Delete "$DESKTOP\Assajjaa.lnk"

	; Remove directories used
	RMDir "$SMPROGRAMS\Assajjaa"
  

SectionEnd