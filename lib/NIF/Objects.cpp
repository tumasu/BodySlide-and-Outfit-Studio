/*
BodySlide and Outfit Studio
Copyright (C) 2017  Caliente & ousnius
See the included LICENSE file
*/

#include "Objects.h"

void NiObjectNET::Get(NiStream& stream) {
	NiObject::Get(stream);

	if (bBSLightingShaderProperty && stream.GetVersion().User() >= 12)
		stream >> skyrimShaderType;

	name.Get(stream);

	extraDataRefs.Get(stream);
	controllerRef.Get(stream);
}

void NiObjectNET::Put(NiStream& stream) {
	NiObject::Put(stream);

	if (bBSLightingShaderProperty && stream.GetVersion().User() >= 12)
		stream << skyrimShaderType;

	name.Put(stream);

	extraDataRefs.Put(stream);
	controllerRef.Put(stream);
}

void NiObjectNET::GetStringRefs(std::set<StringRef*>& refs) {
	NiObject::GetStringRefs(refs);

	refs.insert(&name);
}

std::string NiObjectNET::GetName() {
	return name.GetString();
}

void NiObjectNET::SetName(const std::string& str) {
	name.SetString(str);
}

void NiObjectNET::ClearName() {
	name.Clear();
}

int NiObjectNET::GetControllerRef() {
	return controllerRef.index;
}

void NiObjectNET::SetControllerRef(int ctlrRef) {
	this->controllerRef.index = ctlrRef;
}

int NiObjectNET::GetNumExtraData() {
	return extraDataRefs.GetSize();
}

void NiObjectNET::SetExtraDataRef(const int id, const int blockId) {
	extraDataRefs.SetBlockRef(id, blockId);
}

int NiObjectNET::GetExtraDataRef(const int id) {
	return extraDataRefs.GetBlockRef(id);
}

void NiObjectNET::AddExtraDataRef(const int id) {
	extraDataRefs.AddBlockRef(id);
}

void NiObjectNET::GetChildRefs(std::set<int*>& refs) {
	NiObject::GetChildRefs(refs);

	extraDataRefs.GetIndexPtrs(refs);
	refs.insert(&controllerRef.index);
}


void NiAVObject::Get(NiStream& stream) {
	NiObjectNET::Get(stream);

	flags = 0;
	if (stream.GetVersion().User2() <= 26)
		stream.read((char*)&flags, 2);
	else
		stream >> flags;

	stream >> translation;

	for (int i = 0; i < 3; i++)
		stream >> rotation[i];

	stream >> scale;

	if (stream.GetVersion().User() <= 11)
		propertyRefs.Get(stream);
	
	collisionRef.Get(stream);
}

void NiAVObject::Put(NiStream& stream) {
	NiObjectNET::Put(stream);

	if (stream.GetVersion().User2() <= 26)
		stream.write((char*)&flags, 2);
	else
		stream << flags;

	stream << translation;

	for (int i = 0; i < 3; i++)
		stream << rotation[i];

	stream << scale;

	if (stream.GetVersion().User() <= 11)
		propertyRefs.Put(stream);

	collisionRef.Put(stream);
}

void NiAVObject::GetChildRefs(std::set<int*>& refs) {
	NiObjectNET::GetChildRefs(refs);

	propertyRefs.GetIndexPtrs(refs);
	refs.insert(&collisionRef.index);
}


NiDefaultAVObjectPalette::NiDefaultAVObjectPalette(NiStream& stream) : NiDefaultAVObjectPalette() {
	Get(stream);
}

void NiDefaultAVObjectPalette::Get(NiStream& stream) {
	NiAVObjectPalette::Get(stream);

	sceneRef.Get(stream);

	stream >> numObjects;
	objects.resize(numObjects);
	for (int i = 0; i < numObjects; i++) {
		objects[i].name.Get(stream, 4);
		objects[i].objectRef.Get(stream);
	}
}

void NiDefaultAVObjectPalette::Put(NiStream& stream) {
	NiAVObjectPalette::Put(stream);

	sceneRef.Put(stream);

	stream << numObjects;
	for (int i = 0; i < numObjects; i++) {
		objects[i].name.Put(stream, 4, false);
		objects[i].objectRef.Put(stream);
	}
}

void NiDefaultAVObjectPalette::GetPtrs(std::set<int*>& ptrs) {
	NiAVObjectPalette::GetPtrs(ptrs);

	ptrs.insert(&sceneRef.index);

	for (int i = 0; i < numObjects; i++)
		ptrs.insert(&objects[i].objectRef.index);
}


NiCamera::NiCamera(NiStream& stream) : NiCamera() {
	Get(stream);
}

void NiCamera::Get(NiStream& stream) {
	NiAVObject::Get(stream);

	stream >> obsoleteFlags;
	stream >> frustumLeft;
	stream >> frustumRight;
	stream >> frustumTop;
	stream >> frustomBottom;
	stream >> frustumNear;
	stream >> frustumFar;
	stream >> useOrtho;
	stream >> viewportLeft;
	stream >> viewportRight;
	stream >> viewportTop;
	stream >> viewportBottom;
	stream >> lodAdjust;

	sceneRef.Get(stream);
	stream >> numScreenPolygons;
	stream >> numScreenTextures;
}

void NiCamera::Put(NiStream& stream) {
	NiAVObject::Put(stream);

	stream << obsoleteFlags;
	stream << frustumLeft;
	stream << frustumRight;
	stream << frustumTop;
	stream << frustomBottom;
	stream << frustumNear;
	stream << frustumFar;
	stream << useOrtho;
	stream << viewportLeft;
	stream << viewportRight;
	stream << viewportTop;
	stream << viewportBottom;
	stream << lodAdjust;

	sceneRef.Put(stream);
	stream << numScreenPolygons;
	stream << numScreenTextures;
}

void NiCamera::GetChildRefs(std::set<int*>& refs) {
	NiAVObject::GetChildRefs(refs);

	refs.insert(&sceneRef.index);
}


NiSourceTexture::NiSourceTexture(NiStream& stream) : NiSourceTexture() {
	Get(stream);
}

void NiSourceTexture::Get(NiStream& stream) {
	NiTexture::Get(stream);

	stream >> useExternal;
	fileName.Get(stream);
	dataRef.Get(stream);
	stream >> pixelLayout;
	stream >> mipMapFormat;
	stream >> alphaFormat;
	stream >> isStatic;
	stream >> directRender;
	stream >> persistentRenderData;
}

void NiSourceTexture::Put(NiStream& stream) {
	NiTexture::Put(stream);

	stream << useExternal;
	fileName.Put(stream);
	dataRef.Put(stream);
	stream << pixelLayout;
	stream << mipMapFormat;
	stream << alphaFormat;
	stream << isStatic;
	stream << directRender;
	stream << persistentRenderData;
}

void NiSourceTexture::GetStringRefs(std::set<StringRef*>& refs) {
	NiTexture::GetStringRefs(refs);

	refs.insert(&fileName);
}

void NiSourceTexture::GetChildRefs(std::set<int*>& refs) {
	NiTexture::GetChildRefs(refs);

	refs.insert(&dataRef.index);
}


void NiDynamicEffect::Get(NiStream& stream) {
	NiAVObject::Get(stream);

	if (stream.GetVersion().User2() < 130) {
		stream >> switchState;
		affectedNodes.Get(stream);
	}
}

void NiDynamicEffect::Put(NiStream& stream) {
	NiAVObject::Put(stream);

	if (stream.GetVersion().User2() < 130) {
		stream << switchState;
		affectedNodes.Put(stream);
	}
}

void NiDynamicEffect::GetChildRefs(std::set<int*>& refs) {
	NiAVObject::GetChildRefs(refs);

	affectedNodes.GetIndexPtrs(refs);
}


NiTextureEffect::NiTextureEffect(NiStream& stream) : NiTextureEffect() {
	Get(stream);
}

void NiTextureEffect::Get(NiStream& stream) {
	NiDynamicEffect::Get(stream);

	stream >> modelProjectionMatrix;
	stream >> modelProjectionTransform;
	stream >> textureFiltering;
	stream >> textureClamping;
	stream >> textureType;
	stream >> coordinateGenerationType;
	sourceTexture.Get(stream);
	stream >> clippingPlane;
	stream >> unkVector;
	stream >> unkFloat;
}

void NiTextureEffect::Put(NiStream& stream) {
	NiDynamicEffect::Put(stream);

	stream << modelProjectionMatrix;
	stream << modelProjectionTransform;
	stream << textureFiltering;
	stream << textureClamping;
	stream << textureType;
	stream << coordinateGenerationType;
	sourceTexture.Put(stream);
	stream << clippingPlane;
	stream << unkVector;
	stream << unkFloat;
}

void NiTextureEffect::GetChildRefs(std::set<int*>& refs) {
	NiDynamicEffect::GetChildRefs(refs);

	refs.insert(&sourceTexture.index);
}


void NiLight::Get(NiStream& stream) {
	NiDynamicEffect::Get(stream);

	stream >> dimmer;
	stream >> ambientColor;
	stream >> diffuseColor;
	stream >> specularColor;
}

void NiLight::Put(NiStream& stream) {
	NiDynamicEffect::Put(stream);

	stream << dimmer;
	stream << ambientColor;
	stream << diffuseColor;
	stream << specularColor;
}


NiAmbientLight::NiAmbientLight(NiStream& stream) : NiAmbientLight() {
	Get(stream);
}


NiDirectionalLight::NiDirectionalLight(NiStream& stream) : NiDirectionalLight() {
	Get(stream);
}


NiPointLight::NiPointLight(NiStream& stream) : NiPointLight() {
	Get(stream);
}

void NiPointLight::Get(NiStream& stream) {
	NiLight::Get(stream);

	stream >> constantAttenuation;
	stream >> linearAttenuation;
	stream >> quadraticAttenuation;
}

void NiPointLight::Put(NiStream& stream) {
	NiLight::Put(stream);

	stream << constantAttenuation;
	stream << linearAttenuation;
	stream << quadraticAttenuation;
}


NiSpotLight::NiSpotLight(NiStream& stream) : NiSpotLight() {
	Get(stream);
}

void NiSpotLight::Get(NiStream& stream) {
	NiPointLight::Get(stream);

	stream >> cutoffAngle;
	stream >> unkFloat;
	stream >> exponent;
}

void NiSpotLight::Put(NiStream& stream) {
	NiPointLight::Put(stream);

	stream << cutoffAngle;
	stream << unkFloat;
	stream << exponent;
}
