///////////////////////////////////////////////////////////////////////////////
// Name:        wx/osx/core/stdpaths.h
// Purpose:     wxStandardPaths for CoreFoundation systems
// Author:      David Elliott
// Modified by:
// Created:     2004-10-27
// Copyright:   (c) 2004 David Elliott
// Licence:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

#ifndef _WX_MAC_STDPATHS_H_
#define _WX_MAC_STDPATHS_H_

struct __CFBundle;
struct __CFURL;

typedef const __CFURL * wxCFURLRef;
typedef __CFBundle * wxCFBundleRef;

// we inherit the GUI CF-based wxStandardPaths implementation from the Unix one
// used for console programs if possible (i.e. if we're under a Unix system at
// all)
#if defined(__UNIX__)
    #include "wx/unix/stdpaths.h"
    #define wxStandardPathsCFBase wxStandardPaths
#else
    #define wxStandardPathsCFBase wxStandardPathsBase
#endif

// ----------------------------------------------------------------------------
// wxStandardPaths
// ----------------------------------------------------------------------------

class WXDLLIMPEXP_BASE wxStandardPathsCF : public wxStandardPathsCFBase
{
public:
    virtual ~wxStandardPathsCF();

    // wxMac specific: allow user to specify a different bundle
    wxStandardPathsCF(wxCFBundleRef bundle);
    void SetBundle(wxCFBundleRef bundle);

    // implement base class pure virtuals
    virtual wxString GetExecutablePath() const wxOVERRIDE;
    virtual wxString GetConfigDir() const wxOVERRIDE;
    virtual wxString GetUserConfigDir() const wxOVERRIDE;
    virtual wxString GetDataDir() const wxOVERRIDE;
    virtual wxString GetLocalDataDir() const wxOVERRIDE;
    virtual wxString GetUserDataDir() const wxOVERRIDE;
    virtual wxString GetPluginsDir() const wxOVERRIDE;
    virtual wxString GetResourcesDir() const wxOVERRIDE;
    virtual wxString
    GetLocalizedResourcesDir(const wxString& lang,
                             ResourceCat category = ResourceCat_None) const wxOVERRIDE;
    virtual wxString GetDocumentsDir() const wxOVERRIDE;

protected:
    // Ctor is protected, use wxStandardPaths::Get() instead of instantiating
    // objects of this class directly.
    wxStandardPathsCF();

    // this function can be called with any of CFBundleCopyXXXURL function
    // pointer as parameter
    wxString GetFromFunc(wxCFURLRef (*func)(wxCFBundleRef)) const;

    wxCFBundleRef m_bundle;
};

#endif // _WX_MAC_STDPATHS_H_
