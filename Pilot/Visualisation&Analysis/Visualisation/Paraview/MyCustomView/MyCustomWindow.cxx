/*=========================================================================

   Program: ParaView
   Module:    myMainWindow.cxx

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2. 
   
   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "MyCustomView.h"
#include "ui_myMainWindow.h"

#include "pqApplicationCore.h"
#include "pqPluginManager.h"
#include "pqStandardViewModules.h"
#include "pqRenderView.h"
#include "pqActiveObjects.h"
#include "pqObjectBuilder.h"
#include "pqServerResource.h"
#include "pqPluginManager.h"
#include "pqParaViewMenuBuilders.h"


//-----------------------------------------------------------------------------
MyCustomWindow::MyCustomWindow(QWidget* parentObject,
  Qt::WindowFlags wflags) : Superclass(parentObject, wflags)
{
  pqParaViewMenuBuilders::buildToolbars(*this);

  QString title("My Custom Window");
  this->setWindowTitle(title);
  this->setEnabled(true);
  this->resize(559, 518);
  

  // Get access to the for standard paraview views.
  pqPluginManager* pgm = pqApplicationCore::instance()->getPluginManager();
  pgm->addInterface(new pqStandardViewModules(pgm));

  // Make a connection to the builtin server
  pqApplicationCore* core = pqApplicationCore::instance();
  core->getObjectBuilder()->createServer(pqServerResource("builtin:"));

  // Create render view
  pqRenderView* view = qobject_cast<pqRenderView*>(
    pqApplicationCore::instance()->getObjectBuilder()->createView(
      pqRenderView::renderViewType(),
      pqActiveObjects::instance().activeServer()));

  pqActiveObjects::instance().setActiveView(view);

  QWorkspace * ws = new QWorkspace();
  ws->addWindow(view->getWidget());
  this->setCentralWidget(ws);

}


//-----------------------------------------------------------------------------
MyCustomWindow::~MyCustomWindow()
{
}