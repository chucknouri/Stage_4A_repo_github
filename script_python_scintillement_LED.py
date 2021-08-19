# -*- coding: utf-8 -*-
"""
Created on Sat Jul 10 15:04:39 2021

@author: nouri
"""

import pyluos #importation de la librairie Luos
from pyluos import Device #importation de la classe Device 
                          #qui définit toutes les nodes sur le réseau Luos

device = Device('COM3')#Définition du port sur lequel est connecté le réseau

device.rgb_led_mod.color = [50,80,5]#Envoie des informations au format 
                                    #[Rouge,Vert, Bleu] à l'attribut (node) 
                                    #rgb_led_mod (notre LED)

print(device.containers)#affichage de toutes les nodes présentes sur le réseau.

