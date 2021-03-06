#pragma once
/*
*      Copyright (C) 2015 Team XBMC
*      http://kodi.tv
*
*  This Program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2, or (at your option)
*  any later version.
*
*  This Program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*  GNU General Public License for more details.
*
*  You should have received a copy of the GNU General Public License
*  along with XBMC; see the file COPYING.  If not, see
*  <http://www.gnu.org/licenses/>.
*
*/

#include <map>
#include <string>

#include "interfaces/python/PythonInvoker.h"
#include "network/httprequesthandler/IHTTPRequestHandler.h"
#include "network/httprequesthandler/python/HTTPPythonInvoker.h"
#include "network/httprequesthandler/python/HTTPPythonRequest.h"

namespace XBMCAddon
{
  namespace xbmcwsgi
  {
    class WsgiResponse;
  }
}

class CHTTPPythonWsgiInvoker : public CHTTPPythonInvoker
{
public:
  CHTTPPythonWsgiInvoker(ILanguageInvocationHandler* invocationHandler, HTTPPythonRequest* request);
  ~CHTTPPythonWsgiInvoker() override;

  // implementations of CHTTPPythonInvoker
  HTTPPythonRequest* GetRequest() override;

protected:
  // overrides of CPythonInvoker
  void executeScript(void *fp, const std::string &script, void *module, void *moduleDict) override;
  std::map<std::string, PythonModuleInitialization> getModules() const override;
  const char* getInitializationScript() const override;

private:
  static std::map<std::string, std::string> createCgiEnvironment(const HTTPPythonRequest* httpRequest, ADDON::AddonPtr addon);
  static void addWsgiEnvironment(HTTPPythonRequest* request, void* environment);

  XBMCAddon::xbmcwsgi::WsgiResponse* m_wsgiResponse;
};
