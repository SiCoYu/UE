#include "MyProject.h"
#include "MTestUProperty.h"
#include "Components/DrawSphereComponent.h"
//#include "Components/WindPointSourceComponent.h"

AMTestUProperty::AMTestUProperty()
{
    // Create a new component and give it a name.
    //WindPointSource = CreateDefaultSubobject<UWindPointSourceComponent>(TEXT("WindPointSourceComponent0"));

    // Set our new component as the RootComponent of this actor, or attach it to the root if one already exists.
    //if (RootComponent == nullptr)
    //{
    //    RootComponent = WindPointSource;
    //}
    //else
    //{
    //    WindPointSource->AttachTo(RootComponent);
    //}

    // Create a second component. This will be attached to the component we just created.
    DisplaySphere = CreateDefaultSubobject<UDrawSphereComponent>(TEXT("DrawSphereComponent0"));

	// UE4.17 : warning C4996: 'USceneComponent::AttachTo': This function is deprecated, please use AttachToComponent instead. Please update your code to the new API before upgrading to the next release, otherwise your project will no longer compile.
    //DisplaySphere->AttachTo(RootComponent);
	DisplaySphere->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    // Set some properties on the new component.
    DisplaySphere->ShapeColor.R = 173;
    DisplaySphere->ShapeColor.G = 239;
    DisplaySphere->ShapeColor.B = 231;
    DisplaySphere->ShapeColor.A = 255;
    DisplaySphere->AlwaysLoadOnClient = false;
    DisplaySphere->AlwaysLoadOnServer = false;
    DisplaySphere->bAbsoluteScale = true;
}