AMTestUProperty::AMTestUProperty()
{
    // Create a new component and give it a name.
    WindPointSource = CreateDefaultSubobject<UWindPointSourceComponent>(TEXT("WindPointSourceComponent0"));

    // Set our new component as the RootComponent of this actor, or attach it to the root if one already exists.
    if (RootComponent == nullptr)
    {
        RootComponent = WindPointSource;
    }
    else
    {
        WindPointSource->AttachTo(RootComponent);
    }

    // Create a second component. This will be attached to the component we just created.
    DisplaySphere = CreateDefaultSubobject<UDrawSphereComponent>(TEXT("DrawSphereComponent0"));
    DisplaySphere->AttachTo(RootComponent);

    // Set some properties on the new component.
    DisplaySphere->ShapeColor.R = 173;
    DisplaySphere->ShapeColor.G = 239;
    DisplaySphere->ShapeColor.B = 231;
    DisplaySphere->ShapeColor.A = 255;
    DisplaySphere->AlwaysLoadOnClient = false;
    DisplaySphere->AlwaysLoadOnServer = false;
    DisplaySphere->bAbsoluteScale = true;
}