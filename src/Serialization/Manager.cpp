#include "Serialization/Manager.h"

#include "Serialization/Events.h"
#include "Serialization/Form/Keywords.h"
#include "Serialization/Form/Perks.h"


namespace Serialization
{
	std::string DecodeTypeCode(std::uint32_t a_typeCode)
	{
		constexpr std::size_t SIZE = sizeof(std::uint32_t);

		std::string sig;
		sig.resize(SIZE);
		char* iter = reinterpret_cast<char*>(&a_typeCode);
		for (std::size_t i = 0, j = SIZE - 2; i < SIZE - 1; ++i, --j) {
			sig[j] = iter[i];
		}
		return sig;
	}


	void SaveCallback(SKSE::SerializationInterface* a_intfc)
	{
		using namespace Form;
		using namespace ScriptEvents;
		using namespace StoryEvents;
		using namespace HookedEvents;

		//forms
		auto perks = Perks::GetSingleton();
		if (!perks->GetData(kAdd).empty()) {
			if (!perks->Save(a_intfc, kAddPerks, kSerializationVersion, kAdd)) {
				logger::critical("[Add Perks] : Failed to save data!");
				perks->Clear(kAdd);
			}
		}
		if (!perks->GetData(kRemove).empty()) {
			if (!perks->Save(a_intfc, kRemovePerks, kSerializationVersion, kRemove)) {
				logger::critical("[Remove Perks] : Failed to save data!");
				perks->Clear(kRemove);
			}
		}

		auto keywords = Keywords::GetSingleton();
		if (!keywords->GetData(kAdd).empty()) {
			if (!keywords->Save(a_intfc, kAddKeywords, kSerializationVersion, kAdd)) {
				logger::critical("[Add Keywords] : Failed to save data!");
				keywords->Clear(true);
			}
		}
		if (!keywords->GetData(kRemove).empty()) {
			if (!keywords->Save(a_intfc, kRemoveKeywords, kSerializationVersion, kRemove)) {
				logger::critical("[Remove Keywords] : Failed to save data!");
				keywords->Clear(kRemove);
			}
		}

		//script events
		auto cellFullyLoaded = OnCellFullyLoadedRegSet::GetSingleton();
		if (!cellFullyLoaded->Save(a_intfc, kOnCellFullyLoaded, kSerializationVersion)) {
			logger::critical("Failed to save OnCellFullyLoaded regs!");
		}

		auto questStart = OnQuestStartRegMap::GetSingleton();
		if (!questStart->Save(a_intfc, kQuestStart, kSerializationVersion)) {
			logger::critical("Failed to save QuestStart regs!");
		}

		auto questStop = OnQuestStopRegMap::GetSingleton();
		if (!questStop->Save(a_intfc, kQuestStop, kSerializationVersion)) {
			logger::critical("Failed to save QuestStop regs!");
		}

		auto questStage = OnQuestStageRegMap::GetSingleton();
		if (!questStage->Save(a_intfc, kQuestStage, kSerializationVersion)) {
			logger::critical("Failed to save QuestStage regs!");
		}

		auto objectLoad = OnObjectLoadedRegMap::GetSingleton();
		if (!objectLoad->Save(a_intfc, kObjectLoaded, kSerializationVersion)) {
			logger::critical("Failed to save ObjectLoaded regs!");
		}

		auto objectUnload = OnObjectUnloadedRegMap::GetSingleton();
		if (!objectUnload->Save(a_intfc, kObjectUnloaded, kSerializationVersion)) {
			logger::critical("Failed to save ObjectUnloaded regs!");
		}

		auto objectGrab = OnGrabRegSet::GetSingleton();
		if (!objectGrab->Save(a_intfc, kGrab, kSerializationVersion)) {
			logger::critical("Failed to save ObjectGrab regs!");
		}

		auto objectRelease = OnReleaseRegSet::GetSingleton();
		if (!objectRelease->Save(a_intfc, kRelease, kSerializationVersion)) {
			logger::critical("Failed to save ObjectRelease regs!");
		}

		// story events
		auto actorKill = OnActorKillRegSet::GetSingleton();
		if (!actorKill->Save(a_intfc, kActorKill, kSerializationVersion)) {
			logger::critical("Failed to save ActorKill regs!");
		}

		auto booksRead = OnBooksReadRegSet::GetSingleton();
		if (!booksRead->Save(a_intfc, kBookRead, kSerializationVersion)) {
			logger::critical("Failed to save BooksRead regs!");
		}

		auto criticalHit = OnCriticalHitRegSet::GetSingleton();
		if (!criticalHit->Save(a_intfc, kCritHit, kSerializationVersion)) {
			logger::critical("Failed to save CriticalHit regs!");
		}

		auto disarmed = OnDisarmedRegSet::GetSingleton();
		if (!disarmed->Save(a_intfc, kDisarm, kSerializationVersion)) {
			logger::critical("Failed to save Disarmed regs!");
		}

		auto dragonSoul = OnDragonSoulsGainedRegSet::GetSingleton();
		if (!dragonSoul->Save(a_intfc, kDragonSoul, kSerializationVersion)) {
			logger::critical("Failed to save DragonSoul regs!");
		}

		auto harvest = OnItemHarvestedRegSet::GetSingleton();
		if (!harvest->Save(a_intfc, kHarvest, kSerializationVersion)) {
			logger::critical("Failed to save ItemHarvested regs!");
		}

		auto levelIncrease = OnLevelIncreaseRegSet::GetSingleton();
		if (!levelIncrease->Save(a_intfc, kLevelIncrease, kSerializationVersion)) {
			logger::critical("Failed to save LevelIncrease regs!");
		}

		auto locDiscovery = OnLocationDiscoveryRegSet::GetSingleton();
		if (!locDiscovery->Save(a_intfc, kLocDiscovery, kSerializationVersion)) {
			logger::critical("Failed to save LocDiscovery regs!");
		}

		auto skillIncrease = OnSkillIncreaseRegSet::GetSingleton();
		if (!skillIncrease->Save(a_intfc, kSkillIncrease, kSerializationVersion)) {
			logger::critical("Failed to save SkillIncrease regs!");
		}

		auto shoutAttack = OnShoutAttackRegSet::GetSingleton();
		if (!shoutAttack->Save(a_intfc, kShoutAttack, kSerializationVersion)) {
			logger::critical("Failed to save ShoutAttack regs!");
		}

		auto soulTrap = OnSoulsTrappedRegSet::GetSingleton();
		if (!soulTrap->Save(a_intfc, kSoulTrap, kSerializationVersion)) {
			logger::critical("Failed to save SoulTrap regs!");
		}

		auto spellLearned = OnSpellsLearnedRegSet::GetSingleton();
		if (!spellLearned->Save(a_intfc, kSpellLearned, kSerializationVersion)) {
			logger::critical("Failed to save SpellLearned regs!");
		}

		//hooked events
		auto actorResurrect = OnActorResurrectRegSet::GetSingleton();
		if (!actorResurrect->Save(a_intfc, kActorResurrect, kSerializationVersion)) {
			logger::critical("Failed to save ActorResurrect regs!");
		}

		auto actorReanimateStart = OnActorReanimateStartRegSet::GetSingleton();
		if (!actorReanimateStart->Save(a_intfc, kActorReanimateStart, kSerializationVersion)) {
			logger::critical("Failed to save ActorReanimateStart regs!");
		}

		auto actorReanimateStop = OnActorReanimateStopRegSet::GetSingleton();
		if (!actorReanimateStop->Save(a_intfc, kActorReanimateStop, kSerializationVersion)) {
			logger::critical("Failed to save ActorReanimateStop regs!");
		}

		auto weatherChange = OnWeatherChangeRegSet::GetSingleton();
		if (!weatherChange->Save(a_intfc, kWeatherChange, kSerializationVersion)) {
			logger::critical("Failed to save WeatherChange regs!");
		}

		logger::info("Finished saving data");
	}


	void LoadCallback(SKSE::SerializationInterface* a_intfc)
	{
		using namespace Form;
		using namespace ScriptEvents;
		using namespace StoryEvents;
		using namespace HookedEvents;

		auto perks = Perks::GetSingleton();
		auto keywords = Keywords::GetSingleton();

		std::uint32_t type;
		std::uint32_t version;
		std::uint32_t length;
		while (a_intfc->GetNextRecordInfo(type, version, length)) {
			if (version != kSerializationVersion) {
				logger::critical("Loaded data is out of date! Read ({}), expected ({}) for type code ({})", version, kSerializationVersion, DecodeTypeCode(type));
				continue;
			}

			switch (type) {
			case kAddPerks:
				{
					perks->Clear(Form::kAdd);
					if (!perks->Load(a_intfc, Form::kAdd)) {
						logger::critical("Failed to load AddPerks reg!");
					} else {
						perks->LoadData(Form::kAdd);
					}
				}
				break;
			case kRemovePerks:
				{
					perks->Clear(Form::kRemove);
					if (!perks->Load(a_intfc, Form::kRemove)) {
						logger::critical("Failed to load RemovePerks reg!");
					} else {
						perks->LoadData(Form::kRemove);
					}
				}
				break;
			case kAddKeywords:
				{
					keywords->Clear(Form::kAdd);
					if (!keywords->Load(a_intfc, Form::kAdd)) {
						logger::critical("Failed to load AddKeywords reg!");
					} else {
						keywords->LoadData(Form::kAdd);
					}
				}
				break;
			case kRemoveKeywords:
				{
					keywords->Clear(Form::kRemove);
					if (!keywords->Load(a_intfc, Form::kRemove)) {
						logger::critical("Failed to load RemoveKeywords reg!");
					} else {
						keywords->LoadData(Form::kRemove);
					}
				}
				break;
			case kOnCellFullyLoaded:
				{
					auto regs = OnCellFullyLoadedRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load OnCellFullyLoaded regs!");
					}
				}
				break;
			case kQuestStart:
				{
					auto regs = OnQuestStartRegMap::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load QuestStart regs!");
					}
				}
				break;
			case kQuestStop:
				{
					auto regs = OnQuestStopRegMap::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load QuestStop regs!");
					}
				}
				break;
			case kQuestStage:
				{
					auto regs = OnQuestStageRegMap::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load QuestStage regs!");
					}
				}
				break;
			case kObjectLoaded:
				{
					auto regs = OnObjectLoadedRegMap::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ObjectLoaded regs!");
					}
				}
				break;
			case kObjectUnloaded:
				{
					auto regs = OnObjectUnloadedRegMap::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ObjectUnloaded regs!");
					}
				}
				break;
			case kGrab:
				{
					auto regs = OnGrabRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ObjectGrab regs!");
					}
				}
				break;
			case kRelease:
				{
					auto regs = OnReleaseRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ObjectRelease regs!");
					}
				}
				break;
			case kActorKill:
				{
					auto regs = OnActorKillRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ActorKill regs!");
					}
				}
				break;
			case kBookRead:
				{
					auto regs = OnBooksReadRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load BooksRead regs!");
					}
				}
				break;
			case kCritHit:
				{
					auto regs = OnCriticalHitRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load CriticalHit regs!");
					}
				}
				break;
			case kDisarm:
				{
					auto regs = OnDisarmedRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load Disarmed regs!");
					}
				}
				break;
			case kDragonSoul:
				{
					auto regs = OnDragonSoulsGainedRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load DragonSoulsGained regs!");
					}
				}
				break;
			case kHarvest:
				{
					auto regs = OnItemHarvestedRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ItemHarvested regs!");
					}
				}
				break;
			case kLevelIncrease:
				{
					auto regs = OnLevelIncreaseRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load CriticalHit regs!");
					}
				}
				break;
			case kLocDiscovery:
				{
					auto regs = OnLocationDiscoveryRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load LocationDiscovery regs!");
					}
				}
				break;
			case kShoutAttack:
				{
					auto regs = OnShoutAttackRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ShoutAttack regs!");
					}
				}
				break;
			case kSkillIncrease:
				{
					auto regs = OnSkillIncreaseRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load SkillIncrease regs!");
					}
				}
				break;
			case kSoulTrap:
				{
					auto regs = OnSoulsTrappedRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load Soul Trap regs!");
					}
				}
				break;
			case kSpellLearned:
				{
					auto regs = OnSpellsLearnedRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load SpellsLearned regs!");
					}
				}
				break;
			case kActorResurrect:
				{
					auto regs = OnActorResurrectRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ActorResurrect regs!");
					}
				}
				break;
			case kActorReanimateStart:
				{
					auto regs = OnActorReanimateStartRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ActorReanimateStart regs!");
					}
				}
				break;
			case kActorReanimateStop:
				{
					auto regs = OnActorReanimateStopRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load ActorReanimateStop regs!");
					}
				}
				break;
			case kWeatherChange:
				{
					auto regs = OnWeatherChangeRegSet::GetSingleton();
					regs->Clear();
					if (!regs->Load(a_intfc)) {
						logger::critical("Failed to load WeatherChange regs!");
					}
				}
				break;
			default:
				logger::critical("Unrecognized record type ({})!", DecodeTypeCode(type));
				break;
			}
		}

		logger::info("Finished loading data");
	}
}
