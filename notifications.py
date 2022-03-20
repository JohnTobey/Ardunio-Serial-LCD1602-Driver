#Fusion of https://askubuntu.com/questions/38733/how-to-read-dbus-monitor-output?rq=1 Keto's answer
#https://stackoverflow.com/questions/55374626/how-to-read-notifications-using-d-bus-and-python-3

import dbus
import gi.repository.GLib
from dbus.mainloop.glib import DBusGMainLoop

def filter_cb(bus, message):
	# the NameAcquired message comes through before match string gets applied
	if message.get_member() != "Notify":
		return
	args = message.get_args_list()
	# args are
	# (app_name, notification_id, icon, summary, body, actions, hints, timeout)
	print(args[3]+ ": " + args[4])


DBusGMainLoop(set_as_default=True)

bus = dbus.SessionBus()
bus.add_match_string_non_blocking("eavesdrop=true, interface='org.freedesktop.Notifications', member='Notify'")
bus.add_message_filter(filter_cb)

mainloop = gi.repository.GLib.MainLoop()
mainloop.run()

