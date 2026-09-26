module;
#include <mustache/ecs/archetype.hpp>
#include <mustache/ecs/base_job.hpp>
#include <mustache/ecs/component_events.hpp>
#include <mustache/ecs/component_factory.hpp>
#include <mustache/ecs/component_handler.hpp>
#include <mustache/ecs/component_info.hpp>
#include <mustache/ecs/component_mask.hpp>
#include <mustache/ecs/ecs.hpp>
#include <mustache/ecs/entity.hpp>
#include <mustache/ecs/entity_builder.hpp>
#include <mustache/ecs/entity_group.hpp>
#include <mustache/ecs/entity_manager.hpp>
#include <mustache/ecs/event_manager.hpp>
#include <mustache/ecs/non_template_job.hpp>
#include <mustache/ecs/shared_component.hpp>
#include <mustache/ecs/system.hpp>
#include <mustache/ecs/system_manager.hpp>
#include <mustache/ecs/task_view.hpp>
#include <mustache/ecs/world.hpp>
#include <mustache/ecs/world_filter.hpp>
#include <mustache/ecs/world_storage.hpp>
#include <mustache/ext/add_remove_events.hpp>
#include <mustache/utils/default_settings.hpp>
#include <mustache/utils/dispatch.hpp>
#include <mustache/utils/memory_manager.hpp>
export module ModdersDream.Mustache;

export namespace ModdersDream::Mustache {

// Worlds and entities.
using World = ::mustache::World;
using WorldContext = ::mustache::WorldContext;
using WorldStorage = ::mustache::WorldStorage;
using SingletonId = ::mustache::SingletonId;
using ObjectTag = ::mustache::ObjectTag;
using Entity = ::mustache::Entity;
using EntityId = ::mustache::EntityId;
using EntityVersion = ::mustache::EntityVersion;
using WorldId = ::mustache::WorldId;
using WorldVersion = ::mustache::WorldVersion;
using CloneEntityMap = ::mustache::CloneEntityMap;
using EntityManager = ::mustache::EntityManager;
using EntityGroup = ::mustache::EntityGroup;
using EntityLocationInWorld = ::mustache::EntityLocationInWorld;
using ArchetypeChunkSize = ::mustache::ArchetypeChunkSize;
using ArchetypeChunkSizeFunction = ::mustache::ArchetypeChunkSizeFunction;

// Archetypes and component identifiers.
using Archetype = ::mustache::Archetype;
using ArchetypeComponents = ::mustache::ArchetypeComponents;
using ArchetypeFilterParam = ::mustache::ArchetypeFilterParam;
using ArchetypeIndex = ::mustache::ArchetypeIndex;
using TaskArchetypeIndex = ::mustache::TaskArchetypeIndex;
using ArchetypeEntityIndex = ::mustache::ArchetypeEntityIndex;
using ChunkItemIndex = ::mustache::ChunkItemIndex;
using ChunkCapacity = ::mustache::ChunkCapacity;
using DataLocation = ::mustache::DataLocation;
using ChunkIndex = ::mustache::ChunkIndex;
using ComponentStorageIndex = ::mustache::ComponentStorageIndex;
using ComponentId = ::mustache::ComponentId;
using SharedComponentId = ::mustache::SharedComponentId;
using ComponentIndex = ::mustache::ComponentIndex;
using SharedComponentIndex = ::mustache::SharedComponentIndex;
using ComponentArraySize = ::mustache::ComponentArraySize;
using ComponentOffset = ::mustache::ComponentOffset;

// Component registration and masks.
using ComponentFactory = ::mustache::ComponentFactory;
using ComponentInfo = ::mustache::ComponentInfo;
using ComponentIdMask = ::mustache::ComponentIdMask;
using SharedComponentIdMask = ::mustache::SharedComponentIdMask;
using ComponentIndexMask = ::mustache::ComponentIndexMask;
using SharedComponentPtr = ::mustache::SharedComponentPtr;
using SharedComponentsData = ::mustache::SharedComponentsData;
using SharedComponentsInfo = ::mustache::SharedComponentsInfo;
using SharedComponentTag = ::mustache::SharedComponentTag;
using MaskAndVersion = ::mustache::MaskAndVersion;

// Systems.
using SystemConfig = ::mustache::SystemConfig;
using SystemState = ::mustache::SystemState;
using ASystem = ::mustache::ASystem;
using SystemManager = ::mustache::SystemManager;

// Jobs and filtering.
using BaseJob = ::mustache::BaseJob;
using NonTemplateJob = ::mustache::NonTemplateJob;
using JobUnroll = ::mustache::JobUnroll;
using JobRunMode = ::mustache::JobRunMode;
using JobInvocationIndex = ::mustache::JobInvocationIndex;
using TasksCount = ::mustache::TasksCount;
using JobSize = ::mustache::JobSize;
using TaskSize = ::mustache::TaskSize;
using TaskInfo = ::mustache::TaskInfo;
using ArrayView = ::mustache::ArrayView;
using ArchetypeGroup = ::mustache::ArchetypeGroup;
using TaskGroup = ::mustache::TaskGroup;
using WorldFilterParam = ::mustache::WorldFilterParam;
using FilterCheckParam = ::mustache::FilterCheckParam;
using FilterSetParam = ::mustache::FilterSetParam;
using WorldFilterResult = ::mustache::WorldFilterResult;

// Events.
using EventId = ::mustache::EventId;
using EventManager = ::mustache::EventManager;
using AReceivers = ::mustache::AReceivers;

// Dispatch and memory.
using ThreadId = ::mustache::ThreadId;
using Job = ::mustache::Job;
using QueueId = ::mustache::QueueId;
using CommonQueuePriority = ::mustache::CommonQueuePriority;
using Queue = ::mustache::Queue;
using ParallelTaskId = ::mustache::ParallelTaskId;
using ParallelTaskItemIndexInTask = ::mustache::ParallelTaskItemIndexInTask;
using ParallelTaskGlobalItemIndex = ::mustache::ParallelTaskGlobalItemIndex;
using Dispatcher = ::mustache::Dispatcher;
using MemoryManager = ::mustache::MemoryManager;

// Safety.
using FunctionSafety = ::mustache::FunctionSafety;

// Entity builders.
template <typename C, typename Args>
using ComponentArg = ::mustache::ComponentArg<C, Args>;
template <typename TupleType>
using EntityBuilder = ::mustache::EntityBuilder<TupleType>;

// Component templates.
template <typename Signature>
using Functor = ::mustache::Functor<Signature>;
template <typename T>
using CloneDest = ::mustache::CloneDest<T>;
template <typename T>
using CloneSource = ::mustache::CloneSource<T>;
template <typename ItemType, size_t MaxElements>
using ComponentMask = ::mustache::ComponentMask<ItemType, MaxElements>;
template <typename ItemType>
using DynamicComponentMask = ::mustache::DynamicComponentMask<ItemType>;
template <typename T>
using TSharedComponentTag = ::mustache::TSharedComponentTag<T>;
template <typename T>
using Component = ::mustache::Component<T>;
template <typename T, bool IsRequired>
using ComponentHandler = ::mustache::ComponentHandler<T, IsRequired>;
template <typename T>
using RequiredComponent = ::mustache::RequiredComponent<T>;
template <typename T>
using OptionalComponent = ::mustache::OptionalComponent<T>;
template <typename T>
using SharedComponent = ::mustache::SharedComponent<T>;
template <typename T>
using ComponentType = ::mustache::ComponentType<T>;
template <typename T>
using IsComponentMutable = ::mustache::IsComponentMutable<T>;
template <typename T>
using IsComponentRequired = ::mustache::IsComponentRequired<T>;
template <typename T>
using IsComponentOptional = ::mustache::IsComponentOptional<T>;

// System and job templates.
template <typename T>
using System = ::mustache::System<T>;
template <typename T, JobUnroll Unroll = JobUnroll::kAuto>
using PerEntityJob = ::mustache::PerEntityJob<T, Unroll>;
template <typename Function, JobUnroll Unroll = JobUnroll::kAuto>
using SimpleTask = ::mustache::SimpleTask<Function, Unroll>;

// Event templates.
template <typename T>
using Receiver = ::mustache::Receiver<T>;
template <typename T>
using Receivers = ::mustache::Receivers<T>;
template <typename T>
using ComponentAssingEvent = ::mustache::ComponentAssingEvent<T>;
template <typename T>
using ComponentRemoveEvent = ::mustache::ComponentRemoveEvent<T>;

// Memory allocation.
template <typename T>
using Allocator = ::mustache::Allocator<T>;

using ::mustache::isComponentShared;
using ::mustache::isSafe;

// Component notification extensions.
namespace Ext {

using CommonComponentAssignedEvent = ::mustache::ext::CommonComponentAssignedEvent;
using CommonComponentRemovedEvent = ::mustache::ext::CommonComponentRemovedEvent;

template <typename T>
using ComponentAssignEvent = ::mustache::ext::ComponentAssignEvent<T>;

template <typename T>
using ComponentRemovedEvent = ::mustache::ext::ComponentRemovedEvent<T>;

template <typename T, bool EmitAssignEvent = true, bool EmitRemoveEvent = true>
using ComponentWithNotify = ::mustache::ext::ComponentWithNotify<T, EmitAssignEvent, EmitRemoveEvent>;

template <typename T, bool EmitAssignEvent = true, bool EmitRemoveEvent = true>
using ComponentWithNotifyCommon = ::mustache::ext::ComponentWithNotifyCommon<T, EmitAssignEvent, EmitRemoveEvent>;

} // namespace Ext

} // namespace ModdersDream::Mustache
