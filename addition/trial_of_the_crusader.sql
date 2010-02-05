-- instance
UPDATE instance_template SET script='instance_trial_of_the_crusader' WHERE map=649;

-- announcers
UPDATE creature_template SET npcflag=1, scriptname='Barrett_Ramsey' WHERE entry IN (34816, 35910, 35035, 35766, 35770, 35771, 35909, 35895);

-- two jormungar
UPDATE creature_template SET scriptname='npc_acidmaw' WHERE entry = 35144;
UPDATE creature_template SET scriptname='npc_dreadscale' WHERE entry =34799;

-- argent challenge
UPDATE creature_template SET scriptname='gormok_the_impaler' WHERE entry=34796;