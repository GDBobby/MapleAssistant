v1 release
v1.01 release2
v1.02 paladin fix

v1.1 - code rearranged/cleaned
	corsair custom mix added
	dps for different skills displayed concurrently
	clearer usage for elestaff with mages
	small bucc formula error fixed (no longer using lines to account for barrage bonus)
	
v2 SFML port
	no more win32 !
	
	jobinfo.txt rearranged
		weapon info added in to jobinfo
		mob count added to skills
		weapon stat multipliers hardcoded in, ive never seen a pserver change them
	cygnus knights added in
	made it much easier to add in more skills, you no longer need to change code and can stay in the jobinfo.txt
	while not desireable, ele staff multipliers have been hardcoded in the getMultMagic function
	corsair custom mix removed, may be reimplemented in future
	
	v2.0.1
		chain lightning chain reduction removed (commented for easy reintroduction)
		vanish and wind walk delay changed from 60 to 120
		dark impale speed is changed to the same speeds as brandish
		heaven's hammer has been implemented. I'm not 100% sure if the -450ms adjustment is included or not
			heaven's hammer formula is assumed to use only swing multiplier, and have a 90% mastery
		cooldowns have been added to speed slot 6, should now be easier to adjust
		
		made a default case for new classes, will loop through skills and combos, but no special considerations will be made
			str and dex will be main and sub stat respectively
			currently a 3.6 multiplier will be used, I need an easy way to change that, most likely need to reimplement weapons.txt	
	
	

Notes :
-when a dev changes booster from +2 to +3, chain lightning speed is 630, paralyze&angelray is 690

~~~~~~~~
Todo : 
	-want to add support for buff activation times, and taking that from DPS
	-want summon support
	-want multi-target support
	-want to add support for the damage cap
	-want head-to-head charts for all classes, including at different target numbers
	-want a GUI for setting gear stats, including ammo and shields
	-want support for accuracy calculations
	-want to add support for finding exp per hour, map density
	-maybe a GUI for setting mob distance and using attack range to get real scenario DPS comparisons
	-strafesnipe combo needs to be adjusted, its using decimals. Can't shoot 5.5 strafes between each snipe
~~~~~~~~
	

~~~~~~~~~~~~~~
Things that need testing :	
attack speed on bucc skills, currently using vanilla speeds
attack speed on Dark Impale (DrK), currently using crusher speeds
attack speed on all Cygnus skills, some unimplemented, nightwalker is using Night Lord speeds, using Vampire vanilla
ThunderBreaker combos, attack order etc
Heaven's hammer attack speed
	I believe it's close to 2520 at some speed, then Dream has an adjustment which makes it 450ms faster, close to 2070ms
Hero and Dawn Warrior Advanced Combo multiplier, currently assuming its 2.5 and 1.9 respectively
I doubt it does, but need confirmation if Cygnus final attack adds to 3rd or 4th job skills
	
~~~~~~~~~~~~~~


@~@~@~@~@~@~@~@~@
class IDs

bowmaster		0
marksman		1
windarcher		2
darkknight		3
hero			4
paladin			5
dawnwarrior		6
icelightning	7
firepoison		8
bishop			9
blazewizard		10
shadower		11
nightlord		12
nightwalker		13
buccaneer		14
corsair			15
thunderbreaker	16
@~@~@~@~@~@~@~@~@


~@~@~@~@~@~@~@~@~@~
job info layout

Name
mastery
critchance (before SE)
critdmg (before SE, default is 0)
other modifiers default value is 100 (elemental charges, shadow partner, combo, berserk etc)
	Paladin is ordered Holy Fire Lightning Ice
	currently multiplied by 100 to prevent decimals, meaning the default is 100

Attack1 percent1 lines1 mobcount1
speed[0][0], ....speed[0][4]...spamming speed = speed[0][5] if present
	this is looped until endof or combo is read
combo
	loops reading a skill names until endof or combo is read
endof breaks all reading loops, ending the class reading


~@~@~@~@~@~@~@~@~@~

jobinfo.txt notes
	assassinate needs to be the first skill for Shadower, or darksight delay wont be implemented properly
		if assassinate is the first skill in a combo, darksight delay will be applied
		if its the second skill in a combo, darksight delay is not applied
	ass4th needs to be in second skill slot to properly not account for sharp eyes
	combo needs to be in the first mod slot to not apply sharp eyes
	unfortunately, other class combos are a little more complicated and are hand coded. Only shad supports additional combos	