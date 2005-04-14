/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2005 Robert Osfield 
 *
 * This library is open source and may be redistributed and/or modified under  
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or 
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 * OpenSceneGraph Public License for more details.
*/
#include <osgUtil/RenderGraph>

#include <osg/Notify>

using namespace osg;
using namespace osgUtil;

void RenderGraph::reset()
{
    _parent = NULL;
    _stateset = NULL;

    _depth = 0;

    _children.clear();
    _leaves.clear();
}

/** recursively clean the RenderGraph of all its drawables, lights and depths.
  * Leaves children intact, and ready to be populated again.*/
void RenderGraph::clean()
{

    // clean local drawables etc.
    _leaves.clear();

    // call clean on all children.
    for(ChildList::iterator itr=_children.begin();
        itr!=_children.end();
        ++itr)
    {
        itr->second->clean();
    }

}

/** recursively prune the RenderGraph of empty children.*/
void RenderGraph::prune()
{
    std::vector<const osg::StateSet*> toEraseList;

    // call prune on all children.
    for(ChildList::iterator citr=_children.begin();
        citr!=_children.end();
        ++citr)
    {
        citr->second->prune();

        if (citr->second->empty())
        {
            toEraseList.push_back(citr->first);
        }
    }

    for(std::vector<const osg::StateSet*>::iterator eitr=toEraseList.begin();
        eitr!=toEraseList.end();
        ++eitr)
    {
        _children.erase(*eitr);
    }

}
