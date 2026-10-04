namespace GOTHIC_NAMESPACE
{
	auto Hook_oCAIArrow_CanThisCollideWith = Union::CreateHook(
		reinterpret_cast<void*>(zSwitch(0x00619550, 0x0063CA10, 0x00644C10, 0x006A1490)),
		&oCAIArrow::CanThisCollideWith_Hook,
		Union::HookType::Hook_Detours);

	bool CheckConditions(oCAIArrow* arrow, zCVob* vob) {
		if (arrow->ignoreVobList.IsInList(vob))
			return false;

		oCNpc* npc = vob->CastTo<oCNpc>();
		if (!npc)
			return false;
		if (npc->attribute[NPC_ATR_HITPOINTS] >= 1) // G2 API doesn't have oCNpc::isDead
			return false;

		return true;
	}

	int oCAIArrow::CanThisCollideWith_Hook(zCVob* vob) {
		if (CheckConditions(this, vob)) {
			this->AddIgnoreCDVob(vob);
			return 0;
		}
		return (this->*Hook_oCAIArrow_CanThisCollideWith)(vob);
	}
}
