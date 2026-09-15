module;
#include <Common/interface/RefCntAutoPtr.hpp>
#include <Common/interface/ThreadPool.h>
#include <Graphics/GraphicsEngine/interface/APIInfo.h>
#include <Graphics/GraphicsEngine/interface/BlendState.h>
#include <Graphics/GraphicsEngine/interface/BottomLevelAS.h>
#include <Graphics/GraphicsEngine/interface/Buffer.h>
#include <Graphics/GraphicsEngine/interface/BufferView.h>
#include <Graphics/GraphicsEngine/interface/CommandList.h>
#include <Graphics/GraphicsEngine/interface/CommandQueue.h>
#include <Graphics/GraphicsEngine/interface/Dearchiver.h>
#include <Graphics/GraphicsEngine/interface/DepthStencilState.h>
#include <Graphics/GraphicsEngine/interface/DeviceContext.h>
#include <Graphics/GraphicsEngine/interface/DeviceMemory.h>
#include <Graphics/GraphicsEngine/interface/DeviceObject.h>
#include <Graphics/GraphicsEngine/interface/EngineFactory.h>
#include <Graphics/GraphicsEngine/interface/Fence.h>
#include <Graphics/GraphicsEngine/interface/Framebuffer.h>
#include <Graphics/GraphicsEngine/interface/GraphicsTypes.h>
#include <Graphics/GraphicsEngine/interface/GraphicsTypesX.hpp>
#include <Graphics/GraphicsEngine/interface/InputLayout.h>
#include <Graphics/GraphicsEngine/interface/PipelineResourceSignature.h>
#include <Graphics/GraphicsEngine/interface/PipelineState.h>
#include <Graphics/GraphicsEngine/interface/PipelineStateCache.h>
#include <Graphics/GraphicsEngine/interface/Query.h>
#include <Graphics/GraphicsEngine/interface/RasterizerState.h>
#include <Graphics/GraphicsEngine/interface/RenderDevice.h>
#include <Graphics/GraphicsEngine/interface/RenderPass.h>
#include <Graphics/GraphicsEngine/interface/ResourceMapping.h>
#include <Graphics/GraphicsEngine/interface/Sampler.h>
#include <Graphics/GraphicsEngine/interface/Shader.h>
#include <Graphics/GraphicsEngine/interface/ShaderBindingTable.h>
#include <Graphics/GraphicsEngine/interface/ShaderResourceBinding.h>
#include <Graphics/GraphicsEngine/interface/ShaderResourceVariable.h>
#include <Graphics/GraphicsEngine/interface/SwapChain.h>
#include <Graphics/GraphicsEngine/interface/Texture.h>
#include <Graphics/GraphicsEngine/interface/TextureView.h>
#include <Graphics/GraphicsEngine/interface/TopLevelAS.h>
#include <Platforms/interface/NativeWindow.h>
#include <Primitives/interface/BasicTypes.h>
#include <Primitives/interface/DataBlob.h>
#include <Primitives/interface/DebugOutput.h>
#include <Primitives/interface/FileStream.h>
#include <Primitives/interface/InterfaceID.h>
#include <Primitives/interface/MemoryAllocator.h>
#include <Primitives/interface/Object.h>
#include <Primitives/interface/ReferenceCounters.h>
export module md.renderer.diligent;

export namespace md::renderer::diligent {

// Reference-counted ownership.
template <typename T>
using RefCntAutoPtr = Diligent::RefCntAutoPtr<T>;

template <typename T>
using RefCntWeakPtr = Diligent::RefCntWeakPtr<T>;

// Native window and asynchronous compilation.
using NativeWindow = Diligent::NativeWindow;
using ASYNC_TASK_STATUS = Diligent::ASYNC_TASK_STATUS;
using IAsyncTask = Diligent::IAsyncTask;
using IThreadPool = Diligent::IThreadPool;

// BasicTypes
using Float32 = Diligent::Float32;
using Float64 = Diligent::Float64;
using Int64 = Diligent::Int64;
using Int32 = Diligent::Int32;
using Int16 = Diligent::Int16;
using Int8 = Diligent::Int8;
using Uint64 = Diligent::Uint64;
using Uint32 = Diligent::Uint32;
using Uint16 = Diligent::Uint16;
using Uint8 = Diligent::Uint8;
using SizeType = Diligent::SizeType;
using PVoid = Diligent::PVoid;
using CPVoid = Diligent::CPVoid;
using Bool = Diligent::Bool;
using Char = Diligent::Char;
using String = Diligent::String;

// InterfaceID
using INTERFACE_ID = Diligent::INTERFACE_ID;

// Object
using IObject = Diligent::IObject;

// ReferenceCounters
using ReferenceCounterValueType = Diligent::ReferenceCounterValueType;
using IReferenceCounters = Diligent::IReferenceCounters;

// MemoryAllocator
using IMemoryAllocator = Diligent::IMemoryAllocator;

// DataBlob
using IDataBlob = Diligent::IDataBlob;

// FileStream
using IFileStream = Diligent::IFileStream;

// DebugOutput
using DEBUG_MESSAGE_SEVERITY = Diligent::DEBUG_MESSAGE_SEVERITY;
using DebugMessageCallbackType = Diligent::DebugMessageCallbackType;

// APIInfo
using APIInfo = Diligent::APIInfo;

// BlendState
using BLEND_FACTOR = Diligent::BLEND_FACTOR;
using BLEND_OPERATION = Diligent::BLEND_OPERATION;
using COLOR_MASK = Diligent::COLOR_MASK;
using LOGIC_OPERATION = Diligent::LOGIC_OPERATION;
using RenderTargetBlendDesc = Diligent::RenderTargetBlendDesc;
using BlendStateDesc = Diligent::BlendStateDesc;

// BottomLevelAS
using BLASTriangleDesc = Diligent::BLASTriangleDesc;
using BLASBoundingBoxDesc = Diligent::BLASBoundingBoxDesc;
using RAYTRACING_BUILD_AS_FLAGS = Diligent::RAYTRACING_BUILD_AS_FLAGS;
using BottomLevelASDesc = Diligent::BottomLevelASDesc;
using ScratchBufferSizes = Diligent::ScratchBufferSizes;
using IBottomLevelAS = Diligent::IBottomLevelAS;

// Buffer
using BUFFER_MODE = Diligent::BUFFER_MODE;
using MISC_BUFFER_FLAGS = Diligent::MISC_BUFFER_FLAGS;
using BufferDesc = Diligent::BufferDesc;
using BufferData = Diligent::BufferData;
using SparseBufferProperties = Diligent::SparseBufferProperties;
using IBuffer = Diligent::IBuffer;

// BufferView
using BufferFormat = Diligent::BufferFormat;
using BufferViewDesc = Diligent::BufferViewDesc;
using IBufferView = Diligent::IBufferView;

// CommandList
using ICommandList = Diligent::ICommandList;

// CommandQueue
using ICommandQueue = Diligent::ICommandQueue;

// Dearchiver
using ShaderUnpackInfo = Diligent::ShaderUnpackInfo;
using ResourceSignatureUnpackInfo = Diligent::ResourceSignatureUnpackInfo;
using PSO_ARCHIVE_FLAGS = Diligent::PSO_ARCHIVE_FLAGS;
using PSO_UNPACK_FLAGS = Diligent::PSO_UNPACK_FLAGS;
using PipelineStateUnpackInfo = Diligent::PipelineStateUnpackInfo;
using RenderPassUnpackInfo = Diligent::RenderPassUnpackInfo;
using IDearchiver = Diligent::IDearchiver;

// DepthStencilState
using STENCIL_OP = Diligent::STENCIL_OP;
using StencilOpDesc = Diligent::StencilOpDesc;
using DepthStencilStateDesc = Diligent::DepthStencilStateDesc;

// DeviceContext
using DeviceContextDesc = Diligent::DeviceContextDesc;
using DRAW_FLAGS = Diligent::DRAW_FLAGS;
using RESOURCE_STATE_TRANSITION_MODE = Diligent::RESOURCE_STATE_TRANSITION_MODE;
using DrawAttribs = Diligent::DrawAttribs;
using DrawIndexedAttribs = Diligent::DrawIndexedAttribs;
using DrawIndirectAttribs = Diligent::DrawIndirectAttribs;
using DrawIndexedIndirectAttribs = Diligent::DrawIndexedIndirectAttribs;
using DrawMeshAttribsMtl = Diligent::DrawMeshAttribsMtl;
using DrawMeshAttribs = Diligent::DrawMeshAttribs;
using DrawMeshIndirectAttribs = Diligent::DrawMeshIndirectAttribs;
using MultiDrawItem = Diligent::MultiDrawItem;
using MultiDrawAttribs = Diligent::MultiDrawAttribs;
using MultiDrawIndexedItem = Diligent::MultiDrawIndexedItem;
using MultiDrawIndexedAttribs = Diligent::MultiDrawIndexedAttribs;
using CLEAR_DEPTH_STENCIL_FLAGS = Diligent::CLEAR_DEPTH_STENCIL_FLAGS;
using DispatchComputeAttribs = Diligent::DispatchComputeAttribs;
using DispatchComputeIndirectAttribs = Diligent::DispatchComputeIndirectAttribs;
using DispatchTileAttribs = Diligent::DispatchTileAttribs;
using ResolveTextureSubresourceAttribs = Diligent::ResolveTextureSubresourceAttribs;
using SET_VERTEX_BUFFERS_FLAGS = Diligent::SET_VERTEX_BUFFERS_FLAGS;
using Viewport = Diligent::Viewport;
using Rect = Diligent::Rect;
using CopyTextureAttribs = Diligent::CopyTextureAttribs;
using SetRenderTargetsAttribs = Diligent::SetRenderTargetsAttribs;
using BeginRenderPassAttribs = Diligent::BeginRenderPassAttribs;
using RAYTRACING_INSTANCE_FLAGS = Diligent::RAYTRACING_INSTANCE_FLAGS;
using COPY_AS_MODE = Diligent::COPY_AS_MODE;
using RAYTRACING_GEOMETRY_FLAGS = Diligent::RAYTRACING_GEOMETRY_FLAGS;
using BLASBuildTriangleData = Diligent::BLASBuildTriangleData;
using BLASBuildBoundingBoxData = Diligent::BLASBuildBoundingBoxData;
using BuildBLASAttribs = Diligent::BuildBLASAttribs;
using InstanceMatrix = Diligent::InstanceMatrix;
using TLASBuildInstanceData = Diligent::TLASBuildInstanceData;
using BuildTLASAttribs = Diligent::BuildTLASAttribs;
using CopyBLASAttribs = Diligent::CopyBLASAttribs;
using CopyTLASAttribs = Diligent::CopyTLASAttribs;
using WriteBLASCompactedSizeAttribs = Diligent::WriteBLASCompactedSizeAttribs;
using WriteTLASCompactedSizeAttribs = Diligent::WriteTLASCompactedSizeAttribs;
using TraceRaysAttribs = Diligent::TraceRaysAttribs;
using TraceRaysIndirectAttribs = Diligent::TraceRaysIndirectAttribs;
using UpdateIndirectRTBufferAttribs = Diligent::UpdateIndirectRTBufferAttribs;
using SparseBufferMemoryBindRange = Diligent::SparseBufferMemoryBindRange;
using SparseBufferMemoryBindInfo = Diligent::SparseBufferMemoryBindInfo;
using SparseTextureMemoryBindRange = Diligent::SparseTextureMemoryBindRange;
using SparseTextureMemoryBindInfo = Diligent::SparseTextureMemoryBindInfo;
using BindSparseResourceMemoryAttribs = Diligent::BindSparseResourceMemoryAttribs;
using STATE_TRANSITION_FLAGS = Diligent::STATE_TRANSITION_FLAGS;
using StateTransitionDesc = Diligent::StateTransitionDesc;
using DeviceContextCommandCounters = Diligent::DeviceContextCommandCounters;
using DeviceContextStats = Diligent::DeviceContextStats;
using IDeviceContext = Diligent::IDeviceContext;

// DeviceMemory
using DEVICE_MEMORY_TYPE = Diligent::DEVICE_MEMORY_TYPE;
using DeviceMemoryDesc = Diligent::DeviceMemoryDesc;
using DeviceMemoryCreateInfo = Diligent::DeviceMemoryCreateInfo;
using IDeviceMemory = Diligent::IDeviceMemory;

// DeviceObject
using IDeviceObject = Diligent::IDeviceObject;

// EngineFactory
using IShaderSourceInputStreamFactory = Diligent::IShaderSourceInputStreamFactory;
using DearchiverCreateInfo = Diligent::DearchiverCreateInfo;
using IEngineFactory = Diligent::IEngineFactory;

// Fence
using FENCE_TYPE = Diligent::FENCE_TYPE;
using FenceDesc = Diligent::FenceDesc;
using IFence = Diligent::IFence;

// Framebuffer
using FramebufferDesc = Diligent::FramebufferDesc;
using IFramebuffer = Diligent::IFramebuffer;

// GraphicsTypes
using VALUE_TYPE = Diligent::VALUE_TYPE;
using SHADER_TYPE = Diligent::SHADER_TYPE;
using BIND_FLAGS = Diligent::BIND_FLAGS;
using USAGE = Diligent::USAGE;
using CPU_ACCESS_FLAGS = Diligent::CPU_ACCESS_FLAGS;
using MAP_TYPE = Diligent::MAP_TYPE;
using MAP_FLAGS = Diligent::MAP_FLAGS;
using RESOURCE_DIMENSION = Diligent::RESOURCE_DIMENSION;
using TEXTURE_VIEW_TYPE = Diligent::TEXTURE_VIEW_TYPE;
using BUFFER_VIEW_TYPE = Diligent::BUFFER_VIEW_TYPE;
using TEXTURE_FORMAT = Diligent::TEXTURE_FORMAT;
using FILTER_TYPE = Diligent::FILTER_TYPE;
using TEXTURE_ADDRESS_MODE = Diligent::TEXTURE_ADDRESS_MODE;
using COMPARISON_FUNCTION = Diligent::COMPARISON_FUNCTION;
using PRIMITIVE_TOPOLOGY = Diligent::PRIMITIVE_TOPOLOGY;
using MEMORY_PROPERTIES = Diligent::MEMORY_PROPERTIES;
using DepthStencilClearValue = Diligent::DepthStencilClearValue;
using OptimizedClearValue = Diligent::OptimizedClearValue;
using DeviceObjectAttribs = Diligent::DeviceObjectAttribs;
using ADAPTER_TYPE = Diligent::ADAPTER_TYPE;
using SCALING_MODE = Diligent::SCALING_MODE;
using SCANLINE_ORDER = Diligent::SCANLINE_ORDER;
using DisplayModeAttribs = Diligent::DisplayModeAttribs;
using SWAP_CHAIN_USAGE_FLAGS = Diligent::SWAP_CHAIN_USAGE_FLAGS;
using SURFACE_TRANSFORM = Diligent::SURFACE_TRANSFORM;
using SwapChainDesc = Diligent::SwapChainDesc;
using FullScreenModeDesc = Diligent::FullScreenModeDesc;
using QUERY_TYPE = Diligent::QUERY_TYPE;
using RENDER_DEVICE_TYPE = Diligent::RENDER_DEVICE_TYPE;
using DEVICE_FEATURE_STATE = Diligent::DEVICE_FEATURE_STATE;
using DeviceFeatures = Diligent::DeviceFeatures;
using ADAPTER_VENDOR = Diligent::ADAPTER_VENDOR;
using Version = Diligent::Version;
using WAVE_FEATURE = Diligent::WAVE_FEATURE;
using VALIDATION_LEVEL = Diligent::VALIDATION_LEVEL;
using TextureProperties = Diligent::TextureProperties;
using SamplerProperties = Diligent::SamplerProperties;
using WaveOpProperties = Diligent::WaveOpProperties;
using BufferProperties = Diligent::BufferProperties;
using RAY_TRACING_CAP_FLAGS = Diligent::RAY_TRACING_CAP_FLAGS;
using RayTracingProperties = Diligent::RayTracingProperties;
using MeshShaderProperties = Diligent::MeshShaderProperties;
using ComputeShaderProperties = Diligent::ComputeShaderProperties;
using NDCAttribs = Diligent::NDCAttribs;
using RenderDeviceShaderVersionInfo = Diligent::RenderDeviceShaderVersionInfo;
using RenderDeviceInfo = Diligent::RenderDeviceInfo;
using VALIDATION_FLAGS = Diligent::VALIDATION_FLAGS;
using COMMAND_QUEUE_TYPE = Diligent::COMMAND_QUEUE_TYPE;
using QUEUE_PRIORITY = Diligent::QUEUE_PRIORITY;
using AdapterMemoryInfo = Diligent::AdapterMemoryInfo;
using SHADING_RATE_COMBINER = Diligent::SHADING_RATE_COMBINER;
using SHADING_RATE_FORMAT = Diligent::SHADING_RATE_FORMAT;
using AXIS_SHADING_RATE = Diligent::AXIS_SHADING_RATE;
using SHADING_RATE = Diligent::SHADING_RATE;
using SAMPLE_COUNT = Diligent::SAMPLE_COUNT;
using ShadingRateMode = Diligent::ShadingRateMode;
using SHADING_RATE_CAP_FLAGS = Diligent::SHADING_RATE_CAP_FLAGS;
using SHADING_RATE_TEXTURE_ACCESS = Diligent::SHADING_RATE_TEXTURE_ACCESS;
using ShadingRateProperties = Diligent::ShadingRateProperties;
using DRAW_COMMAND_CAP_FLAGS = Diligent::DRAW_COMMAND_CAP_FLAGS;
using DrawCommandProperties = Diligent::DrawCommandProperties;
using SPARSE_RESOURCE_CAP_FLAGS = Diligent::SPARSE_RESOURCE_CAP_FLAGS;
using SparseResourceProperties = Diligent::SparseResourceProperties;
using CommandQueueInfo = Diligent::CommandQueueInfo;
using GraphicsAdapterInfo = Diligent::GraphicsAdapterInfo;
using ImmediateContextCreateInfo = Diligent::ImmediateContextCreateInfo;
using OpenXRAttribs = Diligent::OpenXRAttribs;
using EngineCreateInfo = Diligent::EngineCreateInfo;
using EngineGLCreateInfo = Diligent::EngineGLCreateInfo;
using D3D11_VALIDATION_FLAGS = Diligent::D3D11_VALIDATION_FLAGS;
using EngineD3D11CreateInfo = Diligent::EngineD3D11CreateInfo;
using D3D12_VALIDATION_FLAGS = Diligent::D3D12_VALIDATION_FLAGS;
using EngineD3D12CreateInfo = Diligent::EngineD3D12CreateInfo;
using VulkanDescriptorPoolSize = Diligent::VulkanDescriptorPoolSize;
using DeviceFeaturesVk = Diligent::DeviceFeaturesVk;
using EngineVkCreateInfo = Diligent::EngineVkCreateInfo;
using EngineMtlCreateInfo = Diligent::EngineMtlCreateInfo;
using EngineWebGPUCreateInfo = Diligent::EngineWebGPUCreateInfo;
using Box = Diligent::Box;
using COMPONENT_TYPE = Diligent::COMPONENT_TYPE;
using TextureFormatAttribs = Diligent::TextureFormatAttribs;
using TextureFormatInfo = Diligent::TextureFormatInfo;
using RESOURCE_DIMENSION_SUPPORT = Diligent::RESOURCE_DIMENSION_SUPPORT;
using TextureFormatInfoExt = Diligent::TextureFormatInfoExt;
using SPARSE_TEXTURE_FLAGS = Diligent::SPARSE_TEXTURE_FLAGS;
using SparseTextureFormatInfo = Diligent::SparseTextureFormatInfo;
using PIPELINE_STAGE_FLAGS = Diligent::PIPELINE_STAGE_FLAGS;
using ACCESS_FLAGS = Diligent::ACCESS_FLAGS;
using RESOURCE_STATE = Diligent::RESOURCE_STATE;
using STATE_TRANSITION_TYPE = Diligent::STATE_TRANSITION_TYPE;

// InputLayout
using INPUT_ELEMENT_FREQUENCY = Diligent::INPUT_ELEMENT_FREQUENCY;
using LayoutElement = Diligent::LayoutElement;
using InputLayoutDesc = Diligent::InputLayoutDesc;

// PipelineResourceSignature
using ImmutableSamplerDesc = Diligent::ImmutableSamplerDesc;
using PIPELINE_RESOURCE_FLAGS = Diligent::PIPELINE_RESOURCE_FLAGS;
using WEB_GPU_BINDING_TYPE = Diligent::WEB_GPU_BINDING_TYPE;
using WebGPUResourceAttribs = Diligent::WebGPUResourceAttribs;
using PipelineResourceDesc = Diligent::PipelineResourceDesc;
using PipelineResourceSignatureDesc = Diligent::PipelineResourceSignatureDesc;
using IPipelineResourceSignature = Diligent::IPipelineResourceSignature;

// PipelineState
using SampleDesc = Diligent::SampleDesc;
using SHADER_VARIABLE_FLAGS = Diligent::SHADER_VARIABLE_FLAGS;
using ShaderResourceVariableDesc = Diligent::ShaderResourceVariableDesc;
using PIPELINE_SHADING_RATE_FLAGS = Diligent::PIPELINE_SHADING_RATE_FLAGS;
using PipelineResourceLayoutDesc = Diligent::PipelineResourceLayoutDesc;
using GraphicsPipelineDesc = Diligent::GraphicsPipelineDesc;
using RayTracingGeneralShaderGroup = Diligent::RayTracingGeneralShaderGroup;
using RayTracingTriangleHitShaderGroup = Diligent::RayTracingTriangleHitShaderGroup;
using RayTracingProceduralHitShaderGroup = Diligent::RayTracingProceduralHitShaderGroup;
using RayTracingPipelineDesc = Diligent::RayTracingPipelineDesc;
using PIPELINE_TYPE = Diligent::PIPELINE_TYPE;
using PipelineStateDesc = Diligent::PipelineStateDesc;
using PSO_CREATE_FLAGS = Diligent::PSO_CREATE_FLAGS;
using SpecializationConstant = Diligent::SpecializationConstant;
using PipelineStateCreateInfo = Diligent::PipelineStateCreateInfo;
using GraphicsPipelineStateCreateInfo = Diligent::GraphicsPipelineStateCreateInfo;
using ComputePipelineStateCreateInfo = Diligent::ComputePipelineStateCreateInfo;
using RayTracingPipelineStateCreateInfo = Diligent::RayTracingPipelineStateCreateInfo;
using TilePipelineDesc = Diligent::TilePipelineDesc;
using TilePipelineStateCreateInfo = Diligent::TilePipelineStateCreateInfo;
using PIPELINE_STATE_STATUS = Diligent::PIPELINE_STATE_STATUS;
using IPipelineState = Diligent::IPipelineState;

// PipelineStateCache
using PSO_CACHE_MODE = Diligent::PSO_CACHE_MODE;
using PSO_CACHE_FLAGS = Diligent::PSO_CACHE_FLAGS;
using PipelineStateCacheDesc = Diligent::PipelineStateCacheDesc;
using PipelineStateCacheCreateInfo = Diligent::PipelineStateCacheCreateInfo;
using IPipelineStateCache = Diligent::IPipelineStateCache;

// Query
using QueryDataOcclusion = Diligent::QueryDataOcclusion;
using QueryDataBinaryOcclusion = Diligent::QueryDataBinaryOcclusion;
using QueryDataTimestamp = Diligent::QueryDataTimestamp;
using QueryDataPipelineStatistics = Diligent::QueryDataPipelineStatistics;
using QueryDataDuration = Diligent::QueryDataDuration;
using QueryDesc = Diligent::QueryDesc;
using IQuery = Diligent::IQuery;

// RasterizerState
using FILL_MODE = Diligent::FILL_MODE;
using CULL_MODE = Diligent::CULL_MODE;
using RasterizerStateDesc = Diligent::RasterizerStateDesc;

// RenderDevice
using IRenderDevice = Diligent::IRenderDevice;

// RenderPass
using ATTACHMENT_LOAD_OP = Diligent::ATTACHMENT_LOAD_OP;
using ATTACHMENT_STORE_OP = Diligent::ATTACHMENT_STORE_OP;
using RenderPassAttachmentDesc = Diligent::RenderPassAttachmentDesc;
using AttachmentReference = Diligent::AttachmentReference;
using ShadingRateAttachment = Diligent::ShadingRateAttachment;
using SubpassDesc = Diligent::SubpassDesc;
using SubpassDependencyDesc = Diligent::SubpassDependencyDesc;
using RenderPassDesc = Diligent::RenderPassDesc;
using IRenderPass = Diligent::IRenderPass;

// ResourceMapping
using ResourceMappingEntry = Diligent::ResourceMappingEntry;
using ResourceMappingCreateInfo = Diligent::ResourceMappingCreateInfo;
using IResourceMapping = Diligent::IResourceMapping;

// Sampler
using SAMPLER_FLAGS = Diligent::SAMPLER_FLAGS;
using SamplerDesc = Diligent::SamplerDesc;
using ISampler = Diligent::ISampler;

// Shader
using ShaderVersion = Diligent::ShaderVersion;
using SHADER_SOURCE_LANGUAGE = Diligent::SHADER_SOURCE_LANGUAGE;
using SHADER_COMPILER = Diligent::SHADER_COMPILER;
using CREATE_SHADER_SOURCE_INPUT_STREAM_FLAGS = Diligent::CREATE_SHADER_SOURCE_INPUT_STREAM_FLAGS;
using ShaderDesc = Diligent::ShaderDesc;
using SHADER_STATUS = Diligent::SHADER_STATUS;
using ShaderMacro = Diligent::ShaderMacro;
using ShaderMacroArray = Diligent::ShaderMacroArray;
using SHADER_COMPILE_FLAGS = Diligent::SHADER_COMPILE_FLAGS;
using SHADER_OPTIMIZATION_LEVEL = Diligent::SHADER_OPTIMIZATION_LEVEL;
using ShaderCreateInfo = Diligent::ShaderCreateInfo;
using SHADER_RESOURCE_TYPE = Diligent::SHADER_RESOURCE_TYPE;
using ShaderResourceDesc = Diligent::ShaderResourceDesc;
using SHADER_CODE_BASIC_TYPE = Diligent::SHADER_CODE_BASIC_TYPE;
using SHADER_CODE_VARIABLE_CLASS = Diligent::SHADER_CODE_VARIABLE_CLASS;
using IShader = Diligent::IShader;

// ShaderBindingTable
using ShaderBindingTableDesc = Diligent::ShaderBindingTableDesc;
using VERIFY_SBT_FLAGS = Diligent::VERIFY_SBT_FLAGS;
using IShaderBindingTable = Diligent::IShaderBindingTable;

// ShaderResourceBinding
using IShaderResourceBinding = Diligent::IShaderResourceBinding;

// ShaderResourceVariable
using SHADER_RESOURCE_VARIABLE_TYPE = Diligent::SHADER_RESOURCE_VARIABLE_TYPE;
using SHADER_RESOURCE_VARIABLE_TYPE_FLAGS = Diligent::SHADER_RESOURCE_VARIABLE_TYPE_FLAGS;
using BIND_SHADER_RESOURCES_FLAGS = Diligent::BIND_SHADER_RESOURCES_FLAGS;
using SET_SHADER_RESOURCE_FLAGS = Diligent::SET_SHADER_RESOURCE_FLAGS;
using IShaderResourceVariable = Diligent::IShaderResourceVariable;

// SwapChain
using ISwapChain = Diligent::ISwapChain;

// Texture
using MISC_TEXTURE_FLAGS = Diligent::MISC_TEXTURE_FLAGS;
using TextureDesc = Diligent::TextureDesc;
using TextureSubResData = Diligent::TextureSubResData;
using TextureData = Diligent::TextureData;
using MappedTextureSubresource = Diligent::MappedTextureSubresource;
using SparseTextureProperties = Diligent::SparseTextureProperties;
using ITexture = Diligent::ITexture;

// TextureView
using UAV_ACCESS_FLAG = Diligent::UAV_ACCESS_FLAG;
using TEXTURE_VIEW_FLAGS = Diligent::TEXTURE_VIEW_FLAGS;
using TEXTURE_COMPONENT_SWIZZLE = Diligent::TEXTURE_COMPONENT_SWIZZLE;
using TextureComponentMapping = Diligent::TextureComponentMapping;
using TextureViewDesc = Diligent::TextureViewDesc;
using ITextureView = Diligent::ITextureView;

// TopLevelAS
using TopLevelASDesc = Diligent::TopLevelASDesc;
using HIT_GROUP_BINDING_MODE = Diligent::HIT_GROUP_BINDING_MODE;
using TLASBuildInfo = Diligent::TLASBuildInfo;
using TLASInstanceDesc = Diligent::TLASInstanceDesc;
using ITopLevelAS = Diligent::ITopLevelAS;

// GraphicsTypesX
using SubpassDescX = Diligent::SubpassDescX;
using RenderPassDescX = Diligent::RenderPassDescX;
using InputLayoutDescX = Diligent::InputLayoutDescX;
template <typename DerivedType, typename BaseType>
using DeviceObjectAttribsX = Diligent::DeviceObjectAttribsX<DerivedType, BaseType>;
using FramebufferDescX = Diligent::FramebufferDescX;
using PipelineResourceSignatureDescX = Diligent::PipelineResourceSignatureDescX;
using PipelineResourceLayoutDescX = Diligent::PipelineResourceLayoutDescX;
using BottomLevelASDescX = Diligent::BottomLevelASDescX;
template <typename DerivedType, typename CreateInfoType>
using PipelineStateCreateInfoX = Diligent::PipelineStateCreateInfoX<DerivedType, CreateInfoType>;
using GraphicsPipelineStateCreateInfoX = Diligent::GraphicsPipelineStateCreateInfoX;
using ComputePipelineStateCreateInfoX = Diligent::ComputePipelineStateCreateInfoX;
using TilePipelineStateCreateInfoX = Diligent::TilePipelineStateCreateInfoX;
using RayTracingPipelineStateCreateInfoX = Diligent::RayTracingPipelineStateCreateInfoX;
template <typename T>
using PipelineStateCreateInfoXTraits = Diligent::PipelineStateCreateInfoXTraits<T>;
template <bool ThrowOnError = true>
using RenderDeviceX = Diligent::RenderDeviceX<ThrowOnError>;
using RenderDeviceX_E = Diligent::RenderDeviceX_E;
using RenderDeviceX_N = Diligent::RenderDeviceX_N;
using ShaderResourceVariableX = Diligent::ShaderResourceVariableX;
using MultiDrawAttribsX = Diligent::MultiDrawAttribsX;
using MultiDrawIndexedAttribsX = Diligent::MultiDrawIndexedAttribsX;

} // namespace md::renderer::diligent
