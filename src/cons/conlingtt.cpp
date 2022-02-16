/* -*- tab-width: 4 -*-
 *
 * Electric(tm) VLSI Design System
 *
 * File: conlingtt.c
 * Linear inequality constraint system: graphics-to-text conversion
 * Written by: Steven M. Rubin, Static Free Software
 *
 * Copyright (c) 2000 Static Free Software.
 *
 * Electric(tm) is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Electric(tm) is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Electric(tm); see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, Mass 02111-1307, USA.
 *
 * Static Free Software
 * 4119 Alpine Road
 * Portola Valley, California 94028
 * info@staticfreesoft.com
 */
#include "global.h"
#include "conlin.h"

static WINDOWPART *cli_curwindow;

/* prototypes for local routines */
static void cli_addequivcon(ARCINST*);
static INTBIG cli_findtextconn(ARCINST*);
static CHAR *cli_makearcline(ARCINST*);
static CHAR *cli_makeportline(PORTPROTO*);
static BOOLEAN cli_uniquelayer(ARCINST*);
static INTBIG cli_addcomponentinfo(void*, NODEINST*);
static void cli_addcomponentdata(void*, COMPONENT*);
static CHAR *cli_componentname(NODEINST*);
static void cli_addcomponentline(CHAR*, WINDOWPART*);
static void cli_addattr(void*, ATTR*);
static void cli_addnodeprotoname(void*, NODEPROTO*);

/************************** IDENTIFY EQUIVALENT TEXT **************************/

/*
 * routine to highlight the text that is equivalent to the graphic object "geom"
 */
void cli_highlightequivalent(GEOM *geom)
{
	 NODEPROTO *par;
	 ARCINST *ai;
	 NODEINST *ni;
	 INTBIG i, cindex, total;
	 CHAR *str, *compname;
	 COMPONENTDEC *dec;
	 COMPONENT *compo;

	par = geomparent(geom);
	if (cli_curcell != par) return;

	/* handle pointing to graphics */
	if (!geom->entryisnode)
	{
		ai = geom->entryaddr.ai;
		cindex = cli_findtextconn(ai);
		if (cindex != -1) (void)asktool(us_tool, x_((char*)"edit-highlightline"), (INTBIG)cli_curwindow, cindex);
		return;
	}

	/* highlight the equivalent node */
	ni = geom->entryaddr.ni;
	compname = cli_componentname(ni);
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINEDECL) continue;
		dec = cli_parsecomp(str, FALSE);
		if (dec == NOCOMPONENTDEC) continue;
		if (ni->proto != getnodeproto(dec->protoname))
		{
			cli_deletecomponentdec(dec);
			continue;
		}

		/* search for the changed node */
		for(compo = dec->firstcomponent; compo != NOCOMPONENT; compo = compo->nextcomponent)
			if (namesame(compname, compo->name) == 0) break;
		if (compo != NOCOMPONENT) (void)asktool(us_tool, x_((char*)"edit-highlightline"), (INTBIG)cli_curwindow, i);
		cli_deletecomponentdec(dec);
		return;
	}
}

/**************************** CONVERT ENTIRE CELL ****************************/

/*
 * routine to fill the text window with the description of graphics cell "np".
 * If "np" is NONODEPROTO, turn off the text system.
 */
void cli_maketextcell(NODEPROTO *np)
{
	CHAR *name;
	 CHAR *pt;
	 NODEINST *ni, *oni;
	 PORTPROTO *pp;
	 ARCINST *ai;
	 INTBIG first, lensofar, len, i, trunclen;
	INTBIG chars, lines;
	 void *infstr;

	/* initialize the textual equivalent window */
	cli_curcell = np;
	if (!cli_texton)
	{
		(void)asktool(us_tool, x_((char*)"edit-describe"), (INTBIG)&name);
		infstr = initinfstr();
		addstringtoinfstr(infstr, name);
		addstringtoinfstr(infstr, M_((char*)" Editor equivalence for cell "));
		addstringtoinfstr(infstr, np->protoname);
		(void)allocstring(&name, returninfstr(infstr), el_tempcluster);
		cli_curwindow = cli_makeeditorwindow(name, &chars, &lines);
		efree(name);
		if (cli_curwindow == NOWINDOWPART) return;
	}
	if (np == NONODEPROTO) return;

	/* convert all components into declarations */
	(void)asktool(us_tool, x_((char*)"edit-suspendgraphics"), (INTBIG)cli_curwindow);

	/* erase the window */
	len = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<len; i++)
		(void)asktool(us_tool, x_((char*)"edit-deleteline"), (INTBIG)cli_curwindow, i);

	/* load the cell */
	trunclen = chars / 4 * 3;
	cli_textlines = 0;
	infstr = initinfstr();
	addstringtoinfstr(infstr, x_((char*)"BEGINCELL "));
	addstringtoinfstr(infstr, np->protoname);
	addstringtoinfstr(infstr, x_((char*)";"));
	(void)asktool(us_tool, x_((char*)"edit-addline"), (INTBIG)cli_curwindow, 0, (INTBIG)returninfstr(infstr));
	for(ni = np->firstnodeinst; ni != NONODEINST; ni = ni->nextnodeinst)
		ni->temp1 = 0;
	for(ni = np->firstnodeinst; ni != NONODEINST; ni = ni->nextnodeinst)
	{
		if (ni->temp1 != 0) continue;

		/* gather all of the nodes of this type */
		first = 0;
		lensofar = 0;
		for(oni = np->firstnodeinst; oni != NONODEINST; oni = oni->nextnodeinst)
		{
			if (oni->proto != ni->proto) continue;

			/* try to keep the lines down to a reasonable length */
			if (lensofar > trunclen)
			{
				addtoinfstr(infstr, ' ');
				cli_addnodeprotoname(infstr, ni->proto);
				addtoinfstr(infstr, ';');
				cli_addcomponentline(returninfstr(infstr), cli_curwindow);
				first = 0;
				lensofar = 0;
			}
			if (first == 0)
			{
				infstr = initinfstr();
				addstringtoinfstr(infstr, x_((char*)"declare "));
				lensofar = 8;
				first++;
			} else
			{
				addstringtoinfstr(infstr, x_((char*)", "));
				lensofar += 2;
			}
			pt = cli_componentname(oni);
			lensofar += estrlen(pt);
			addstringtoinfstr(infstr, pt);
			oni->temp1 = 1;

			/* add in size/rotation/location if not default */
			lensofar += cli_addcomponentinfo(infstr, oni);
		}
		if (first != 0)
		{
			addtoinfstr(infstr, ' ');
			cli_addnodeprotoname(infstr, ni->proto);
			addtoinfstr(infstr, ';');
			cli_addcomponentline(returninfstr(infstr), cli_curwindow);
		}
	}

	/* now generate the "export" declarations */
	for(pp = np->firstportproto; pp != NOPORTPROTO; pp = pp->nextportproto)
		cli_addcomponentline(cli_makeportline(pp), cli_curwindow);

	/* now convert the constaints */
	for(ai = np->firstarcinst; ai != NOARCINST; ai = ai->nextarcinst)
		cli_addequivcon(ai);
	cli_replaceendcell(x_((char*)"ENDCELL;"), cli_curwindow);
	(void)asktool(us_tool, x_((char*)"edit-resumegraphics"), (INTBIG)cli_curwindow);
}

/***************************** GRAPHIC CHANGES *****************************/

/*
 * routine to update text when a new graphic node "ni" is created
 */
void cli_eq_newnode(NODEINST *ni)
{
	 COMPONENTDEC *dec;
	 COMPONENT *compo;
	 CHAR *str;
	 INTBIG i, total;
	 void *infstr;

	/* ignore changes generated by constraint results */
	if (cli_ownchanges) return;

	/* ignore changes made to a cell not being equated */
	if (ni->parent != cli_curcell) return;

	/* look for a declaration of this type of node */
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINEDECL) continue;
		dec = cli_parsecomp(str, FALSE);
		if (dec == NOCOMPONENTDEC) continue;
		if (ni->proto != getnodeproto(dec->protoname))
		{
			cli_deletecomponentdec(dec);
			continue;
		}

		/* found the declaration, rebuild with existing components */
		infstr = initinfstr();
		addstringtoinfstr(infstr, x_((char*)"declare "));
		for(compo = dec->firstcomponent; compo != NOCOMPONENT; compo = compo->nextcomponent)
		{
			addstringtoinfstr(infstr, compo->name);
			cli_addcomponentdata(infstr, compo);
			addstringtoinfstr(infstr, x_((char*)", "));
		}

		/* add in the new component */
		addstringtoinfstr(infstr, cli_componentname(ni));
		(void)cli_addcomponentinfo(infstr, ni);
		addtoinfstr(infstr, ' ');

		/* finish the declaration and replace the line */
		addstringtoinfstr(infstr, dec->protoname);
		addtoinfstr(infstr, ';');
		(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i, (INTBIG)returninfstr(infstr));
		cli_deletecomponentdec(dec);
		return;
	}

	/* build a simple declaration for this node */
	infstr = initinfstr();
	addstringtoinfstr(infstr, x_((char*)"declare "));
	addstringtoinfstr(infstr, cli_componentname(ni));
	(void)cli_addcomponentinfo(infstr, ni);
	addtoinfstr(infstr, ' ');
	cli_addnodeprotoname(infstr, ni->proto);
	addtoinfstr(infstr, ';');
	cli_addcomponentline(returninfstr(infstr), cli_curwindow);
}

/*
 * routine to update text when graphic node "ni" is deleted
 */
void cli_eq_killnode(NODEINST *ni)
{
	 CHAR *str, *compname;
	 INTBIG first, i, total;
	 COMPONENTDEC *dec;
	 COMPONENT *compo, *ocomp;
	 void *infstr;

	/* see if node is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;

	/* ignore changes made to a cell not being equated */
	if (ni->parent != cli_curcell) return;

	/* look for a declaration of this type of node */
	compname = cli_componentname(ni);
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINEDECL) continue;
		dec = cli_parsecomp(str, FALSE);
		if (dec == NOCOMPONENTDEC) continue;
		if (ni->proto != getnodeproto(dec->protoname))
		{
			cli_deletecomponentdec(dec);
			continue;
		}

		/* search for the deleted node */
		for(compo = dec->firstcomponent; compo != NOCOMPONENT; compo = compo->nextcomponent)
			if (namesame(compname, compo->name) == 0) break;
		if (compo == NOCOMPONENT)
		{
			cli_deletecomponentdec(dec);
			continue;
		}

		/* delete the line if there are only two keywords */
		if (dec->count == 1 && namesame(dec->firstcomponent->name, compname) == 0)
		{
			/* line had only one keyword: delete the line */
			(void)asktool(us_tool, x_((char*)"edit-deleteline"), (INTBIG)cli_curwindow, i);
			cli_textlines--;
			cli_deletecomponentdec(dec);
			return;
		}

		/* rebuild line without the deleted component */
		infstr = initinfstr();
		addstringtoinfstr(infstr, x_((char*)"declare "));
		first = 0;
		for(ocomp = dec->firstcomponent; ocomp != NOCOMPONENT; ocomp = ocomp->nextcomponent)
		{
			if (compo == ocomp) continue;
			if (first != 0) addstringtoinfstr(infstr, x_((char*)", "));
			first++;
			addstringtoinfstr(infstr, ocomp->name);
			cli_addcomponentdata(infstr, ocomp);
		}
		addtoinfstr(infstr, ' ');
		addstringtoinfstr(infstr, dec->protoname);
		addtoinfstr(infstr, ';');
		(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i, (INTBIG)returninfstr(infstr));
		cli_deletecomponentdec(dec);
		return;
	}
	ttyputmsg(M_((char*)"Warning: cannot find node %s in text"), compname);
}

/* handle the change of node "ni" */
void cli_eq_modnode(NODEINST *ni)
{
	/* see if node is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;
	if (ni->parent == cli_curcell) cli_changeequivcomp(ni);
}

/* handle the creation of new arc "ai" */
void cli_eq_newarc(ARCINST *ai)
{
	 INTBIG i, j;
	 NODEINST *ni;
	 PORTARCINST *pi;

	/* see if arc is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;
	if (ai->parent != cli_curcell) return;

	cli_addequivcon(ai);

	/* see if end nodes now have one connection */
	for(i=0; i<2; i++)
	{
		ni = ai->end[i].nodeinst;
		j = 0;
		for(pi = ni->firstportarcinst; pi != NOPORTARCINST; pi = pi->nextportarcinst) j++;
		if (j == 1) cli_changeequivcomp(ni);
	}
}

/* handle the deletion of arc "ai" */
void cli_eq_killarc(ARCINST *ai)
{
	 NODEINST *ni;
	 INTBIG i;

	/* see if arc is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;
	if (ai->parent != cli_curcell) return;

	cli_deleteequivcon(ai);

	/* see if formerly connecting nodes need redefinition */
	for(i=0; i<2; i++)
	{
		ni = ai->end[i].nodeinst;
		if (ni->firstportarcinst == NOPORTARCINST)
			cli_changeequivcomp(ni);
	}
}

/*
 * routine to handle the change of graphic arc "ai" by making an equivalent
 * change to the text
 */
void cli_eq_modarc(ARCINST *ai)
{
	 CHAR *str;
	 INTBIG cindex;

	/* see if arc is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;

	/* ignore changes made to a cell not being equated */
	if (ai->parent != cli_curcell) return;

	/* get the text node that describes this arc */
	cindex = cli_findtextconn(ai);
	if (cindex == -1)
	{
		ttyputerr(M_((char*)"Cannot find text equivalent for arc %s"), describearcinst(ai));
		return;
	}

	/* build the constraint message */
	str = cli_makearcline(ai);

	/* change the line */
	(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, cindex, (INTBIG)str);
}

/* handle the creation of port "pp" */
void cli_eq_newport(PORTPROTO *pp)
{
	/* see if port is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;
	if (pp->parent != cli_curcell) return;
	cli_addcomponentline(cli_makeportline(pp), cli_curwindow);
}

/* handle the deletion of port "pp" */
void cli_eq_killport(PORTPROTO *pp)
{
	 INTBIG i, total;
	 CHAR *str;
	 EXPORT *e;

	/* see if port is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;
	if (pp->parent != cli_curcell) return;

	/* find the export line with this port */
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		/* get a line of text */
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINEEXPORT) continue;

		/* see if export line is this one */
		e = cli_parseexport(str, FALSE);
		if (e == NOEXPORT) continue;
		if (namesame(pp->protoname, e->portname) != 0)
		{
			cli_deleteexport(e);
			continue;
		}

		/* export line found: delete it */
		(void)asktool(us_tool, x_((char*)"edit-deleteline"), (INTBIG)cli_curwindow, i);
		cli_textlines--;
		cli_deleteexport(e);
		break;
	}
}

/* handle the modification of port "pp" */
void cli_eq_modport(PORTPROTO *pp)
{
	 CHAR *str;
	 EXPORT *e;
	 INTBIG i, total;

	/* see if port is in graphics cell that has equivalent text */
	if (cli_ownchanges) return;
	if (pp->parent != cli_curcell) return;

	/* find the export line with this port */
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		/* get a line of text */
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINEEXPORT) continue;

		/* see if export line is this one */
		e = cli_parseexport(str, FALSE);
		if (e == NOEXPORT) continue;
		if (namesame(pp->protoname, e->portname) != 0)
		{
			cli_deleteexport(e);
			continue;
		}

		/* export line found: rewrite it */
		(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i,
			(INTBIG)cli_makeportline(pp));
		cli_deleteexport(e);
		break;
	}
}

/* handle the creation of variable type "type", name "key", and value "addr" */
void cli_eq_newvar(INTBIG addr, INTBIG type, INTBIG key)
{
	 NODEINST *ni;
	CHAR line[50];
	 VARIABLE *var;

	if (cli_ownchanges) return;

	if (type == VNODEINST)
	{
		/* node added variable: see if this is in a graphics cell */
		ni = (NODEINST *)addr;
		if (ni->parent != cli_curcell) return;

		/* name changes are handled specially */
		if (key == el_node_name_key)
		{
			/* construct the original name */
			(void)esnprintf(line, 50, M_("NODE%ld"), (INTBIG)ni);

			/* get the new node name */
			var = getvalkey((INTBIG)ni, VNODEINST, VSTRING, el_node_name_key);
			if (var == NOVARIABLE) return;
			cli_replacename(line, (CHAR *)var->addr);
			return;
		}

		/* update the declaration */
		cli_changeequivcomp(ni);
		return;
	}

	if (type == VPORTPROTO)
	{
		cli_eq_modport((PORTPROTO *)addr);
		return;
	}

	if (type == VARCINST)
	{
		cli_eq_modarc((ARCINST *)addr);
		return;
	}
}

/* handle the deletion of variable type "type", name "key", and value "addr" */
void cli_eq_killvar(INTBIG addr, INTBIG type, INTBIG key)
{
	CHAR line[50];
	 VARIABLE *var;
	 NODEINST *ni;

	if (cli_ownchanges) return;
	if (type == VNODEINST)
	{
		/* node variable removed: see if this is in a graphics cell */
		ni = (NODEINST *)addr;
		if (ni->parent != cli_curcell) return;

		if (key == el_node_name_key)
		{
			/* get the former name */
			var = getvalkey((INTBIG)ni, VNODEINST, VSTRING, el_node_name_key);
			if (var == NOVARIABLE) return;

			/* construct the new node name */
			(void)esnprintf(line, 50, M_("NODE%ld"), (INTBIG)ni);
			cli_replacename((CHAR *)var->addr, line);
			return;
		}

		/* update the declaration */
		cli_changeequivcomp(ni);
		return;
	}

	if (type == VPORTPROTO)
	{
		cli_eq_modport((PORTPROTO *)addr);
		return;
	}

	if (type == VARCINST)
	{
		cli_eq_modarc((ARCINST *)addr);
		return;
	}
}

void cli_eq_solve(void)
{
	cli_ownchanges = FALSE;
}

/***************************** HELPER ROUTINES *****************************/

/*
 * routine to handle the addition of the text associated with new layout arc "ai"
 */
void cli_addequivcon(ARCINST *ai)
{
	 INTBIG i, total;

	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);

	/* search for the last line with a valid connection declaration */
	for(i = total-1; i >= 0; i--)
		if (cli_linetype((CHAR *)asktool(us_tool, x_((char*)"edit-getline"),
			(INTBIG)cli_curwindow, i)) == LINECONN) break;
	if (i < 0)
	{
		/* no "connect" lines, take last line anywhere */
		i = total-1;
	}
	(void)asktool(us_tool, x_((char*)"edit-addline"), (INTBIG)cli_curwindow, i+1, (INTBIG)cli_makearcline(ai));
	cli_textlines++;
}

/*
 * routine to handle the deletion of the text associated with layout arc "ai"
 */
void cli_deleteequivcon(ARCINST *ai)
{
	 INTBIG cindex;

	/* get the text node that describes this arc */
	cindex = cli_findtextconn(ai);
	if (cindex != -1)
	{
		(void)asktool(us_tool, x_((char*)"edit-deleteline"), (INTBIG)cli_curwindow, cindex);
		cli_textlines--;
	}
}

/*
 * routine to update the text information about of node "ni"
 */
void cli_changeequivcomp(NODEINST *ni)
{
	 CHAR *str, *compname;
	 INTBIG i, total;
	 COMPONENTDEC *dec;
	 COMPONENT *compo, *ocomp;
	 void *infstr;

	/* look for a declaration of this type of node */
	compname = cli_componentname(ni);
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINEDECL) continue;
		dec = cli_parsecomp(str, FALSE);
		if (dec == NOCOMPONENTDEC) continue;
		if (ni->proto != getnodeproto(dec->protoname))
		{
			cli_deletecomponentdec(dec);
			continue;
		}

		/* search for the changed node */
		for(compo = dec->firstcomponent; compo != NOCOMPONENT; compo = compo->nextcomponent)
			if (namesame(compname, compo->name) == 0) break;
		if (compo == NOCOMPONENT)
		{
			cli_deletecomponentdec(dec);
			continue;
		}

		infstr = initinfstr();
		addstringtoinfstr(infstr, x_((char*)"declare "));
		for(ocomp = dec->firstcomponent; ocomp != NOCOMPONENT; ocomp = ocomp->nextcomponent)
		{
			if (ocomp != dec->firstcomponent) addstringtoinfstr(infstr, x_((char*)", "));
			if (compo == ocomp)
			{
				addstringtoinfstr(infstr, cli_componentname(ni));
				(void)cli_addcomponentinfo(infstr, ni);
			} else
			{
				addstringtoinfstr(infstr, ocomp->name);
				cli_addcomponentdata(infstr, ocomp);
			}
		}
		addtoinfstr(infstr, ' ');
		addstringtoinfstr(infstr, dec->protoname);
		addtoinfstr(infstr, ';');
		(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i, (INTBIG)returninfstr(infstr));
		cli_deletecomponentdec(dec);
		return;
	}
	ttyputmsg(M_((char*)"Warning: cannot find node %s in text"), compname);
}

/*
 * routine to replace the name of graphics node "oni" (which used to be called
 * "oldname") with the name "newname"
 */
void cli_replacename(CHAR *oldname, CHAR *newname)
{
	 CHAR *str;
	 INTBIG i, rewrite, total;
	CHAR line[50];
	 EXPORT *e;
	 COMPONENTDEC *dcl;
	 COMPONENT *compo, *ocomp;
	 CONNECTION *dec;
	 CONS *cons;
	 ATTR *a;
	 void *infstr;

	/* look through all statements for the old name */
	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;

		/* search declaration statement */
		if (cli_linetype(str) == LINEDECL)
		{
			dcl = cli_parsecomp(str, FALSE);
			if (dcl == NOCOMPONENTDEC) continue;
			for(compo = dcl->firstcomponent; compo != NOCOMPONENT; compo = compo->nextcomponent)
				if (namesame(oldname, compo->name) == 0) break;
			if (compo == NOCOMPONENT)
			{
				cli_deletecomponentdec(dcl);
				continue;
			}

			/* rewrite the component declaration line */
			infstr = initinfstr();
			addstringtoinfstr(infstr, x_((char*)"declare "));
			for(ocomp = dcl->firstcomponent; ocomp != NOCOMPONENT; ocomp = ocomp->nextcomponent)
			{
				if (ocomp != dcl->firstcomponent) addstringtoinfstr(infstr, x_((char*)", "));
				if (ocomp == compo) addstringtoinfstr(infstr, newname); else
					addstringtoinfstr(infstr, ocomp->name);
				cli_addcomponentdata(infstr, ocomp);
			}
			addtoinfstr(infstr, ' ');
			addstringtoinfstr(infstr, dcl->protoname);
			addtoinfstr(infstr, ';');
			(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i, (INTBIG)returninfstr(infstr));
			cli_deletecomponentdec(dcl);
			continue;
		}

		/* search export statement */
		if (cli_linetype(str) == LINEEXPORT)
		{
			e = cli_parseexport(str, FALSE);
			if (e == NOEXPORT) continue;
			if (namesame(e->component, oldname) != 0)
			{
				cli_deleteexport(e);
				continue;
			}

			/* rewrite the export line */
			infstr = initinfstr();
			addstringtoinfstr(infstr, x_((char*)"export "));
			if ((e->flag&(EXPCHAR|EXPATTR)) != 0)
			{
				if ((e->flag&EXPCHAR) != 0)
				{
					addstringtoinfstr(infstr, x_((char*)"[type="));
					switch (e->bits&STATEBITS)
					{
						case INPORT :
							addstringtoinfstr(infstr, M_((char*)"input")); break;
						case OUTPORT:
							addstringtoinfstr(infstr, M_((char*)"output")); break;
						case BIDIRPORT:
							addstringtoinfstr(infstr, M_((char*)"bidirectional")); break;
						case PWRPORT:
							addstringtoinfstr(infstr, M_((char*)"power")); break;
						case GNDPORT:
							addstringtoinfstr(infstr, M_((char*)"ground")); break;
						case CLKPORT:
							addstringtoinfstr(infstr, M_((char*)"clock")); break;
						case C1PORT:
							addstringtoinfstr(infstr, M_((char*)"clock1")); break;
						case C2PORT:
							addstringtoinfstr(infstr, M_((char*)"clock2")); break;
						case C3PORT:
							addstringtoinfstr(infstr, M_((char*)"clock3")); break;
						case C4PORT:
							addstringtoinfstr(infstr, M_((char*)"clock4")); break;
						case C5PORT:
							addstringtoinfstr(infstr, M_((char*)"clock5")); break;
						case C6PORT:
							addstringtoinfstr(infstr, M_((char*)"clock6")); break;
						case REFOUTPORT:
							addstringtoinfstr(infstr, M_((char*)"refout")); break;
						case REFINPORT:
							addstringtoinfstr(infstr, M_((char*)"refin")); break;
						case REFBASEPORT:
							addstringtoinfstr(infstr, M_((char*)"refbase")); break;
					}
				}
				if ((e->flag&EXPATTR) != 0)
				{
					if ((e->flag&EXPCHAR) == 0) addtoinfstr(infstr, '['); else
						addtoinfstr(infstr, ',');
					for(a = e->firstattr; a != NOATTR; a = a->nextattr)
					{
						if (a != e->firstattr) addtoinfstr(infstr, ',');
						cli_addattr(infstr, a);
					}
				}
				addstringtoinfstr(infstr, x_((char*)"] "));
			}
			addstringtoinfstr(infstr, e->portname);
			addstringtoinfstr(infstr, x_((char*)" is "));
			addstringtoinfstr(infstr, newname);
			if (e->subport != 0)
			{
				addtoinfstr(infstr, ':');
				addstringtoinfstr(infstr, e->subport);
			}
			addtoinfstr(infstr, ';');
			(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i, (INTBIG)returninfstr(infstr));
			cli_deleteexport(e);
			continue;
		}

		/* search connection statement */
		if (cli_linetype(str) == LINECONN)
		{
			dec = cli_parseconn(str, FALSE);
			if (dec == NOCONNECTION) continue;

			/* see if the connection line needs to be rewriten */
			rewrite = 0;
			if ((dec->flag&END1VALID) != 0 && namesame(dec->end1, oldname) == 0)
			{
				(void)reallocstring(&dec->end1, newname, el_tempcluster);
				rewrite++;
			}
			if ((dec->flag&END2VALID) != 0 && namesame(dec->end2, oldname) == 0)
			{
				(void)reallocstring(&dec->end2, newname, el_tempcluster);
				rewrite++;
			}
			if (rewrite == 0)
			{
				cli_deleteconnection(dec);
				continue;
			}

			/* rewrite the connetion line */
			infstr = initinfstr();
			addstringtoinfstr(infstr, x_((char*)"connect "));
			if ((dec->flag&(LAYERVALID|WIDTHVALID|ATTRVALID)) != 0)
			{
				if ((dec->flag&LAYERVALID) != 0)
				{
					addstringtoinfstr(infstr, x_((char*)"[layer="));
					addstringtoinfstr(infstr, dec->layer);
				}
				if ((dec->flag&WIDTHVALID) != 0)
				{
					if ((dec->flag&LAYERVALID) != 0) addtoinfstr(infstr, ','); else
						addtoinfstr(infstr, '[');
					(void)esnprintf(line, 50, x_("width=%s"), latoa(dec->width, 0));
					addstringtoinfstr(infstr, line);
				}
				if ((dec->flag&ATTRVALID) != 0)
				{
					if ((dec->flag&(LAYERVALID|WIDTHVALID)) != 0) addtoinfstr(infstr, ','); else
						addtoinfstr(infstr, '[');
					for(a = dec->firstattr; a != NOATTR; a = a->nextattr)
					{
						if (a != dec->firstattr) addtoinfstr(infstr, ',');
						cli_addattr(infstr, a);
					}
				}
				addstringtoinfstr(infstr, x_((char*)"] "));
			}

			addstringtoinfstr(infstr, dec->end1);
			if ((dec->flag&PORT1VALID) != 0)
			{
				addtoinfstr(infstr, ':');
				addstringtoinfstr(infstr, dec->port1);
			}

			for(cons = dec->firstcons; cons != NOCONS; cons = cons->nextcons)
			{
				addtoinfstr(infstr, ' ');
				addstringtoinfstr(infstr, cons->direction);
				addtoinfstr(infstr, ' ');
				addstringtoinfstr(infstr, frtoa(cons->amount));
				if (cons->flag == 1) addstringtoinfstr(infstr, x_((char*)" or more"));
				if (cons->flag == -1) addstringtoinfstr(infstr, x_((char*)" or less"));
			}

			/* decide whether to print the arc offset */
			if ((dec->flag&OFFSETVALID) != 0)
			{
				(void)esnprintf(line, 50, x_((char*)" [%s,%s]"), latoa(dec->xoff, 0), latoa(dec->yoff, 0));
				addstringtoinfstr(infstr, line);
			}
			addstringtoinfstr(infstr, x_((char*)" to "));
			addstringtoinfstr(infstr, dec->end2);
			if ((dec->flag&PORT2VALID) != 0)
			{
				addtoinfstr(infstr, ':');
				addstringtoinfstr(infstr, dec->port2);
			}
			addstringtoinfstr(infstr, x_((char*)";"));
			(void)asktool(us_tool, x_((char*)"edit-replaceline"), (INTBIG)cli_curwindow, i, (INTBIG)returninfstr(infstr));
			cli_deleteconnection(dec);
		}
	}
}

/***************************** UTILITIES *****************************/

/*
 * routine to find the text line associated with arc "ai".  Returns the line
 * index (-1 if it cannot be found).
 */
INTBIG cli_findtextconn(ARCINST *ai)
{
	 INTBIG i, total;
	 CHAR *str;
	 CONNECTION *dec;

	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)cli_curwindow);
	for(i=0; i<total; i++)
	{
		/* get a valid connection line */
		str = (CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)cli_curwindow, i);
		if (str == NOSTRING) break;
		if (cli_linetype(str) != LINECONN) continue;
		dec = cli_parseconn(str, TRUE);
		if (dec == NOCONNECTION) continue;

		/* must have both ends specified */
		if ((dec->flag&(END1VALID|END2VALID)) != (END1VALID|END2VALID))
		{
			cli_deleteconnection(dec);
			continue;
		}

		/* end nodes must be correct */
		if (namesame(dec->end1, cli_componentname(ai->end[0].nodeinst)) != 0 ||
			namesame(dec->end2, cli_componentname(ai->end[1].nodeinst)) != 0)
		{
			cli_deleteconnection(dec);
			continue;
		}

		/* specified ports must be correct */
		if ((dec->flag&PORT1VALID) != 0 &&
			namesame(dec->port1, ai->end[0].portarcinst->proto->protoname) != 0)
		{
			cli_deleteconnection(dec);
			continue;
		}
		if ((dec->flag&PORT2VALID) != 0 &&
			namesame(dec->port2, ai->end[1].portarcinst->proto->protoname) != 0)
		{
			cli_deleteconnection(dec);
			continue;
		}

		/* line of text found */
		cli_deleteconnection(dec);
		return(i);
	}
	return(-1);
}

/*
 * routine to convert an arc into a line of text with all constraints
 */
CHAR *cli_makearcline(ARCINST *ai)
{
	CHAR line[50];
	 VARIABLE *var;
	 INTBIG i, len;
	 BOOLEAN doit, added;
	 INTBIG conx, cony, xcons, ycons, lambda;
	 LINCON *conptr;
	 void *infstr;

	infstr = initinfstr();
	addstringtoinfstr(infstr, x_((char*)"connect "));
	added = FALSE;
	if (!cli_uniquelayer(ai))
	{
		addstringtoinfstr(infstr, x_((char*)"[layer="));
		addstringtoinfstr(infstr, describearcproto(ai->proto));
		added = TRUE;
	}
	if (ai->width != ai->proto->nominalwidth)
	{
		if (!added) addtoinfstr(infstr, '['); else addtoinfstr(infstr, ',');
		addstringtoinfstr(infstr, x_((char*)"width="));
		addstringtoinfstr(infstr, latoa(ai->width, 0));
		added = TRUE;
	}
	if (ai->numvar != 0) for(i=0; i<ai->numvar; i++)
	{
		var = &ai->firstvar[i];
		if ((var->type&VISARRAY) != 0) continue;
		if (!added) addtoinfstr(infstr, '['); else addtoinfstr(infstr, ',');
		addstringtoinfstr(infstr, (CHAR *)var->key);
		addtoinfstr(infstr, '=');
		addstringtoinfstr(infstr, describevariable(var, -1, 1));
		added = TRUE;
	}
	if (added) addstringtoinfstr(infstr, x_((char*)"] "));
	addstringtoinfstr(infstr, cli_componentname(ai->end[0].nodeinst));
	if (!cli_uniqueport(ai->end[0].nodeinst, ai->end[0].portarcinst->proto))
	{
		addtoinfstr(infstr, ':');
		addstringtoinfstr(infstr, ai->end[0].portarcinst->proto->protoname);
	}
	var = getvalkey((INTBIG)ai, VARCINST, VINTEGER|VISARRAY, cli_properties_key);

	/* initialize the X constraint to be different from the actual arc size */
	xcons = ycons = 0;
	conx = cony = 0;
	if (var != NOVARIABLE)
	{
		len = getlength(var) / LINCONSIZE;
		lambda = lambdaofarc(ai);
		for(i=0; i<len; i++)
		{
			conptr = &((LINCON *)var->addr)[i];

			switch (conptr->variable)
			{
				case CLLEFT:
					xcons++;
					conx = -conptr->value * lambda / WHOLE;
					(void)esnprintf(line, 50, _(" left %s"), latoa(-conx, 0));
					break;
				case CLRIGHT:
					xcons++;
					conx = conptr->value * lambda / WHOLE;
					(void)esnprintf(line, 50, x_(" right %s"), latoa(conx, 0));
					break;
				case CLDOWN:
					ycons++;
					cony = -conptr->value * lambda / WHOLE;
					(void)esnprintf(line, 50, x_((char*)" down %s"), latoa(-cony, 0));
					break;
				case CLUP:
					ycons++;
					cony = conptr->value * lambda / WHOLE;
					(void)esnprintf(line, 50, x_((char*)" up %s"), latoa(cony, 0));
					break;
			}
			addstringtoinfstr(infstr, line);
			if (conptr->oper == 0) addstringtoinfstr(infstr, x_((char*)" or more"));
			if (conptr->oper == 2) addstringtoinfstr(infstr, x_((char*)" or less"));
		}
	}

	/* decide whether to print the arc offset */
	doit = FALSE;
	if (xcons > 1 || ycons > 1) doit = TRUE;
	if (xcons == 0 && ycons == 0) doit = TRUE;
	if (conx != ai->end[1].xpos - ai->end[0].xpos || cony != ai->end[1].ypos - ai->end[0].ypos)
		doit = TRUE;
	if (doit)
	{
		(void)esnprintf(line, 50, x_((char*)" [%s,%s]"), latoa(ai->end[1].xpos - ai->end[0].xpos, 0),
			latoa(ai->end[1].ypos - ai->end[0].ypos, 0));
		addstringtoinfstr(infstr, line);
	}
	addstringtoinfstr(infstr, x_((char*)" to "));
	addstringtoinfstr(infstr, cli_componentname(ai->end[1].nodeinst));
	if (!cli_uniqueport(ai->end[1].nodeinst, ai->end[1].portarcinst->proto))
	{
		addtoinfstr(infstr, ':');
		addstringtoinfstr(infstr, ai->end[1].portarcinst->proto->protoname);
	}
	addstringtoinfstr(infstr, x_((char*)";"));
	return(returninfstr(infstr));
}

/*
 * routine to handle the addition of the text associated with new port "pp"
 */
CHAR *cli_makeportline(PORTPROTO *pp)
{
	 BOOLEAN added;
	 INTBIG i;
	 VARIABLE *var;
	 void *infstr;

	infstr = initinfstr();
	addstringtoinfstr(infstr, x_((char*)"export "));
	if ((pp->userbits&STATEBITS) != 0)
	{
		addstringtoinfstr(infstr, x_((char*)"[type="));
		switch (pp->userbits&STATEBITS)
		{
			case INPORT:      addstringtoinfstr(infstr, x_((char*)"input"));         break;
			case OUTPORT:     addstringtoinfstr(infstr, x_((char*)"output"));        break;
			case BIDIRPORT:   addstringtoinfstr(infstr, x_((char*)"bidirectional")); break;
			case PWRPORT:     addstringtoinfstr(infstr, x_((char*)"power"));         break;
			case GNDPORT:     addstringtoinfstr(infstr, x_((char*)"ground"));        break;
			case CLKPORT:     addstringtoinfstr(infstr, x_((char*)"clock"));         break;
			case C1PORT:      addstringtoinfstr(infstr, x_((char*)"clock1"));        break;
			case C2PORT:      addstringtoinfstr(infstr, x_((char*)"clock2"));        break;
			case C3PORT:      addstringtoinfstr(infstr, x_((char*)"clock3"));        break;
			case C4PORT:      addstringtoinfstr(infstr, x_((char*)"clock4"));        break;
			case C5PORT:      addstringtoinfstr(infstr, x_((char*)"clock5"));        break;
			case C6PORT:      addstringtoinfstr(infstr, x_((char*)"clock6"));        break;
			case REFOUTPORT:  addstringtoinfstr(infstr, x_((char*)"refout"));        break;
			case REFINPORT:   addstringtoinfstr(infstr, x_((char*)"refin"));         break;
			case REFBASEPORT: addstringtoinfstr(infstr, x_((char*)"refbase"));       break;
				
		}
		added = TRUE;
	} else added = FALSE;

	for(i=0; i<pp->numvar; i++)
	{
		var = &pp->firstvar[i];
		if ((var->type&VISARRAY) != 0) continue;
		if (!added) addtoinfstr(infstr, '['); else addtoinfstr(infstr, ',');
		addstringtoinfstr(infstr, (CHAR *)var->key);
		addtoinfstr(infstr, '=');
		addstringtoinfstr(infstr, describevariable(var, -1, 1));
		added = TRUE;
	}
	if (added) addstringtoinfstr(infstr, x_((char*)"] "));

	addstringtoinfstr(infstr, pp->protoname);
	addstringtoinfstr(infstr, x_((char*)" is "));
	addstringtoinfstr(infstr, cli_componentname(pp->subnodeinst));
	if (!cli_uniqueport(pp->subnodeinst, pp->subportproto))
	{
		addtoinfstr(infstr, ':');
		addstringtoinfstr(infstr, pp->subportproto->protoname);
	}
	addtoinfstr(infstr, ';');
	return(returninfstr(infstr));
}

/*
 * routine to tell whether port "pp" of node "ni" is unique on its node
 * returns true if the port is unique
 */
BOOLEAN cli_uniqueport(NODEINST *ni, PORTPROTO *pp)
{
	 PORTPROTO *opp;
	static POLYGON *poly1 = NOPOLYGON, *poly2 = NOPOLYGON;

	/* make sure polygons are allocated */
	(void)needstaticpolygon(&poly1, 4, cli_constraint->cluster);
	(void)needstaticpolygon(&poly2, 4, cli_constraint->cluster);

	/* get polygon for original port */
	shapeportpoly(ni, pp, poly1, FALSE);

	/* look for a different port */
	for(opp = ni->proto->firstportproto; opp != NOPORTPROTO; opp = opp->nextportproto)
	{
		if (opp == pp) continue;
		shapeportpoly(ni, opp, poly2, FALSE);

		/* if the polygons differ, this port is not unique */
		if (!polysame(poly1, poly2)) return(FALSE);
	}

	/* all polygons the same: port is unique */
	return(TRUE);
}

/*
 * routine to tell whether arc "ai" could be in any other layer
 * Returns true if the layer is unique
 */
BOOLEAN cli_uniquelayer(ARCINST *ai)
{
	 TECHNOLOGY *tech;
	 ARCPROTO *ap;
	 PORTPROTO *pp;
	 INTBIG i;

	/* clear all bits on arcs in this technology */
	tech = ai->proto->tech;
	for(ap = tech->firstarcproto; ap != NOARCPROTO; ap = ap->nextarcproto)
		ap->temp1 = 0;

	/* set bits for the allowable arcs at one end of the arc */
	pp = ai->end[0].portarcinst->proto;
	for(i=0; pp->connects[i] != NOARCPROTO; i++)
		pp->connects[i]->temp1++;

	/* set bits for the allowable arcs at the other end of the arc */
	pp = ai->end[1].portarcinst->proto;
	for(i=0; pp->connects[i] != NOARCPROTO; i++)
		pp->connects[i]->temp1++;

	/* count the number of arcs that can connect to both ends */
	i = 0;
	for(ap = tech->firstarcproto; ap != NOARCPROTO; ap = ap->nextarcproto)
		if (ap->temp1 == 2) i++;

	/* arc layer is not unique if more than one arc can make the connection */
	if (i > 1) return(FALSE);
	return(TRUE);
}

/*
 * routine to add to the infinite string the size/location/rotation factors for
 * the component "ni" if it is not the default.  Returns the number of characters
 * that were added to the string
 */
INTBIG cli_addcomponentinfo(void *infstr, NODEINST *ni)
{
	CHAR line[50];
	 CHAR *st;
	 INTBIG added, i;
	 VARIABLE *var;
	INTBIG plx, phx, ply, phy;

	/* add in component size */
	added = 0;
	if (ni->highx-ni->lowx != ni->proto->highx-ni->proto->lowx ||
		ni->highy-ni->lowy != ni->proto->highy-ni->proto->lowy)
	{
		nodesizeoffset(ni, &plx, &ply, &phx, &phy);
		(void)esnprintf(line, 50, x_("[size=(%s,%s)"), latoa(ni->highx-ni->lowx-plx-phx, 0),
			latoa(ni->highy-ni->lowy-ply-phy, 0));
		addstringtoinfstr(infstr, line);
		added += estrlen(line);
	}

	/* add in component rotation */
	if (ni->rotation != 0 || ni->transpose != 0)
	{
		if (added != 0) addtoinfstr(infstr, ','); else addtoinfstr(infstr, '[');
		(void)esnprintf(line, 50, x_("rotation=%s"), frtoa(ni->rotation*WHOLE/10));
		addstringtoinfstr(infstr, line);
		added += estrlen(line) + 1;
		if (ni->transpose != 0)
		{
			addtoinfstr(infstr, 't');
			added++;
		}
	}

	/* add in component location */
	if (ni->firstportarcinst == NOPORTARCINST)
	{
		if (added != 0) addtoinfstr(infstr, ','); else addtoinfstr(infstr, '[');
		(void)esnprintf(line, 50, x_("location=(%s,%s)"), latoa((ni->highx+ni->lowx) / 2, 0),
			latoa((ni->highy+ni->lowy) / 2, 0));
		addstringtoinfstr(infstr, line);
		added += estrlen(line) + 1;
	}

	/* add additional variables */
	if (ni->numvar != 0) for(i=0; i<ni->numvar; i++)
	{
		var = &ni->firstvar[i];
		if (var->key == el_node_name_key) continue;
		if ((var->type&VISARRAY) != 0) continue;

		if (added != 0) addtoinfstr(infstr, ','); else addtoinfstr(infstr, '[');
		added++;
		addstringtoinfstr(infstr, (CHAR *)var->key);
		addtoinfstr(infstr, '=');
		added += estrlen((CHAR *)var->key) + 1;
		st = describevariable(var, -1, 1);
		added += estrlen(st);
		addstringtoinfstr(infstr, st);
	}

	if (added == 0) return(0);
	addtoinfstr(infstr, ']');
	return(added+1);
}

/*
 * routine to add any options of component "compo" to the infinite string
 */
void cli_addcomponentdata(void *infstr, COMPONENT *compo)
{
	CHAR line[50];
	 ATTR *a;

	if ((compo->flag&(COMPSIZE|COMPROT|COMPLOC|COMPATTR)) != 0)
	{
		addtoinfstr(infstr, '[');
		if ((compo->flag&COMPSIZE) != 0)
		{
			(void)esnprintf(line, 50, x_("size=(%s,%s)"), latoa(compo->sizex, 0), latoa(compo->sizey, 0));
			addstringtoinfstr(infstr, line);
		}
		if ((compo->flag&COMPROT) != 0)
		{
			if ((compo->flag&COMPSIZE) != 0) addtoinfstr(infstr, ',');
			(void)esnprintf(line, 50, x_("rotation=%s"), frtoa(compo->rot*WHOLE/10));
			addstringtoinfstr(infstr, line);
			if (compo->trans != 0) addtoinfstr(infstr, 't');
		}
		if ((compo->flag&COMPLOC) != 0)
		{
			if ((compo->flag&(COMPSIZE|COMPROT)) != 0) addtoinfstr(infstr, ',');
			(void)esnprintf(line, 50, x_("location=(%s,%s)"), latoa(compo->locx, 0), latoa(compo->locy, 0));
			addstringtoinfstr(infstr, line);
		}
		if ((compo->flag&COMPATTR) != 0)
		{
			if ((compo->flag&(COMPSIZE|COMPROT|COMPLOC)) != 0) addtoinfstr(infstr, ',');
			for(a = compo->firstattr; a != NOATTR; a = a->nextattr)
			{
				if (a != compo->firstattr) addtoinfstr(infstr, ',');
				cli_addattr(infstr, a);
			}
		}
		addtoinfstr(infstr, ']');
	}
}

/*
 * routine to return the component name for node "ni"
 */
CHAR *cli_componentname(NODEINST *ni)
{
	static CHAR line[50];
	 VARIABLE *var;

	var = getvalkey((INTBIG)ni, VNODEINST, VSTRING, el_node_name_key);
	if (var == NOVARIABLE)
	{
		(void)esnprintf(line, 50, x_((char*)"NODE%ld"), (INTBIG)ni);
		return(line);
	}
	return((CHAR *)var->addr);
}

void cli_addcomponentline(CHAR *str, WINDOWPART *win)
{
	 INTBIG i, total;

	total = asktool(us_tool, x_((char*)"edit-totallines"), (INTBIG)win);

	/* search for the last line with a valid component declaration */
	for(i = total-1; i >= 0; i--)
		if (cli_linetype((CHAR *)asktool(us_tool, x_((char*)"edit-getline"), (INTBIG)win, i)) == LINEDECL) break;
	if (i < 0) i = 0;
	(void)asktool(us_tool, x_((char*)"edit-addline"), (INTBIG)win, i+1, (INTBIG)str);
	cli_textlines++;
}

void cli_addattr(void *infstr, ATTR *a)
{
	CHAR line[50];

	addstringtoinfstr(infstr, a->name);
	addtoinfstr(infstr, '=');
	if ((a->type&VTYPE) == VINTEGER)
	{
		(void)esnprintf(line, 50, x_("%ld"), a->value);
		addstringtoinfstr(infstr, line);
	} else
	{
		addtoinfstr(infstr, '"');
		addstringtoinfstr(infstr, (CHAR *)a->value);
		addtoinfstr(infstr, '"');
	}
}

/*
 * routine to add the name of nodeproto "np" to the inifinte string
 */
void cli_addnodeprotoname(void *infstr, NODEPROTO *np)
{
	if (np->primindex != 0)
	{
		if (np->tech != el_curtech)
		{
			addstringtoinfstr(infstr, np->tech->techname);
			addtoinfstr(infstr, ':');
		}
		addstringtoinfstr(infstr, np->protoname);
	} else addstringtoinfstr(infstr, np->protoname);
}
