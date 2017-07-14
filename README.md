# Aquarium

Das sind meine ersten Versuche mit dem Quantum Leaps' QP™-nano active object framework und dem QM™ modeling tool.

Mir gefallen die Konzepte des frameworks, wie z.B. die verschachtelten states, welche mir viel doppelte Arbeit ersparen. Ich muss dadurch z.B. nicht alle states einzeln mit dem NotAus-Signal verknüpfen, sondern nur einmalig mit dem obersten state, da ein event automatisch von einem substate an den jeweils höheren state weitergeleitet wird, ggf. so oft, bzw. so lange bis er dem state zugeordnet ist.

Dazu kommt die Möglichkeit der Programmierung von entry und exit actions für jeden state, wodurch ich eine Aktion beim Betreten ein- und beim Verlassen ausschalten kann. Das ist eine sehr aufgeräumte Methode.

Ferner muss ich die Eingangssignale nicht verriegeln und entprellen, da beim ersten Auftreten eines Signals entweder in den nächsten state gewechselt wird oder im bereits aktiven verblieben wird.

Hat man in der ino-Datei alle benötigten Signale deklariert, kann man mit dem modeling tool sehr übersichtlich die Programmstruktur erstellen und in den og. entry und exit actions programmieren.
