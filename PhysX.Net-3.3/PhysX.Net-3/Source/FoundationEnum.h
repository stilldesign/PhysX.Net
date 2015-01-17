#pragma once


namespace PhysX
{
	public enum class ActorClientBehaviorFlag
	{
		ReportToForeignClientsTriggerNotify = PxActorClientBehaviorFlag::eREPORT_TO_FOREIGN_CLIENTS_TRIGGER_NOTIFY,
		ReportToForeignClientsContactNotify = PxActorClientBehaviorFlag::eREPORT_TO_FOREIGN_CLIENTS_CONTACT_NOTIFY,
		ReportToForeignClientsConstraintBreakNotify = PxActorClientBehaviorFlag::eREPORT_TO_FOREIGN_CLIENTS_CONSTRAINT_BREAK_NOTIFY,
		ReportToForeignClientsSceneQuery = PxActorClientBehaviorFlag::eREPORT_TO_FOREIGN_CLIENTS_SCENE_QUERY
	};
};