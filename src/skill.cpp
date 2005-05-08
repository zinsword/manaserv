/*
 *  The Mana World Server
 *  Copyright 2004 The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  The Mana World is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  The Mana World is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Mana World; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  $Id$
 */

#include "skill.h"
#include "log.h"

Skill::~Skill() {
    //cleanup
    for (int i = 0; i < children.size(); i++) {
	if (children[i])
	    delete children[i];
    }
}

bool Skill::addSkill(const std::string &ident, Skill *skill) {
    if (ident == id) {
	//add skill to children
	children.push_back(skill);
	return true;
    }

    for (int i = 0; i < children.size(); i++) {
	//recurse
	if (children[i]->addSkill(ident, skill))
	    return true;
    }
    return false;
}

bool Skill::deleteSkill(const std::string &ident, bool delTree) {
    //prevent deletion of self
    if (ident == id) {
	std::cerr << "Error: Skill: Attempt to delete self." << std::endl;
    logger->log("Error: Skill: Attempt to delete self.");
	return false;
    }

    for (int i = 0; i < children.size(); i++) {
	if (children[i]->id == ident) {
	    if (children[i]->children.size() > 0 && delTree)
		return false;
	    else {
		//delete skill & remove from children
		std::vector<Skill*>::iterator tmp = children.begin() + i;
		delete children[i];
		children.erase(tmp);

		return true;
	    }
	} else {
	    //recurse
	    if (children[i]->deleteSkill(ident))
		return true;
	}
    }
    return false;
}