UE4 学习文档

==================
(1)
资源:
房燕良-虚幻4渲染系统架构解析.pdf
来源:
虚幻4渲染系统结构解析 
http://blog.csdn.net/pizi0475/article/details/52876062

本文根据小米互娱 VR 技术专家 房燕良在 MDCC 2016 移动开发者大会上的演讲整理而成
PPT 下载地址：http://download.csdn.NET/detail/sinat_14921509/9639244。

========================
详细介绍了 Trowbridge-Reitz (GGX)
Implementation of GTR BRDF in V-Ray 3.10
http://help.chaosgroup.com/vray/images/stuff/gtr_tests/gtr_render.html

This page shows some results from the implementation in V-Ray 3.10 of the Generalized-Trowbridge-Reitz BRDF as described in the paper "Physically-Based Shading at Disney". It is an extended version of the GGX BRDF and in addition to the glossiness value, it has another parameter which allows finer control of the hilight shape.

http://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf

=====================
s2012_pbs_disney_brdf_notes_v2.pdf
http://disney-animation.s3.amazonaws.com/library/s2012_pbs_disney_brdf_notes_v2.pdf

===================
高光BRDF化简公式总结（转） 
http://blog.csdn.net/aidlife/article/details/46792177

源：http://graphicrants.blogspot.com/2013/08/specular-brdf-reference.html

Specular BRDF Reference
While I worked on our new shading model for UE4 I tried many different options for our specular BRDF. Specifically, I tried many different terms for to Cook-Torrance microfacet specular BRDF:
f(l,v)=D(h)F(v,h)G(l,v,h)4(n⋅l)(n⋅v)
Directly comparing different terms requires being able to swap them while still using the same input parameters. I thought it might be a useful reference to put these all in one place using the same symbols and same inputs. I will use the same form as Naty [1], so please look there for background and theory. I'd like to keep this as a living reference so if you have useful additions or suggestions let me know.

First let me define alpha that will be used for all following equations using UE4's roughness:
α=roughness2

Normal Distribution Function (NDF)
The NDF, also known as the specular distribution, describes the distribution of microfacets for the surface. It is normalized [12] such that:
∫ΩD(m)(n⋅m)dωi=1
It is interesting to notice all models have 1πα2 for the normalization factor in the isotropic case.

Blinn-Phong [2]:
DBlinn(m)=1πα2(n⋅m)(2α2−2)
This is not the common form but follows when power=2α2−2.
Beckmann [3]:
DBeckmann(m)=1πα2(n⋅m)4exp((n⋅m)2−1α2(n⋅m)2)

GGX (Trowbridge-Reitz) [4]:
DGGX(m)=α2π((n⋅m)2(α2−1)+1)2

GGX Anisotropic [5]:
DGGXaniso(m)=1παxαy1((x⋅m)2α2x+(y⋅m)2α2y+(n⋅m)2)2


Geometric Shadowing
The geometric shadowing term describes the shadowing from the microfacets. This means ideally it should depend on roughness and the microfacet distribution.
Implicit [1]:
GImplicit(l,v,h)=(n⋅l)(n⋅v)

Neumann [6]:
GNeumann(l,v,h)=(n⋅l)(n⋅v)max(n⋅l,n⋅v)

Cook-Torrance [11]:
GCook−Torrance(l,v,h)=min(1,2(n⋅h)(n⋅v)v⋅h,2(n⋅h)(n⋅l)v⋅h)

Kelemen [7]:
GKelemen(l,v,h)=(n⋅l)(n⋅v)(v⋅h)2


Smith
The following geometric shadowing models use Smith's method[8] for their respective NDF. Smith breaks G into two components: light and view, and uses the same equation for both:
G(l,v,h)=G1(l)G1(v)
I will define G1 below for each model and skip duplicating the above equation.

Beckmann [4]:
c=n⋅vα1−(n⋅v)2−−−−−−−−−√
GBeckmann(v)={3.535c+2.181c21+2.276c+2.577c21if c<1.6if c≥1.6

Blinn-Phong:
The Smith integral has no closed form solution for Blinn-Phong. Walter [4] suggests using the same equation as Beckmann.

GGX [4]:
GGGX(v)=2(n⋅v)(n⋅v)+α2+(1−α2)(n⋅v)2−−−−−−−−−−−−−−−−−√
This is not the common form but is a simple refactor by multiplying by n⋅vn⋅v.

Schlick-Beckmann:
Schlick [9] approximated the Smith equation for Beckmann. Naty [1] warns that Schlick approximated the wrong version of Smith, so be sure to compare to the Smith version before using.
k=α2π−−√
GSchlick(v)=n⋅v(n⋅v)(1−k)+k

Schlick-GGX:
For UE4, I used the Schlick approximation and matched it to the GGX Smith formulation by remapping k [10]:
k=α2


Fresnel
The Fresnel function describes the amount of light that reflects from a mirror surface given its index of refraction. Instead of using IOR we instead use the parameter or F0 which is the reflectance at normal incidence.

None:
FNone(v,h)=F0

Schlick [9]:
FSchlick(v,h)=F0+(1−F0)(1−(v⋅h))5

Cook-Torrance [11]:
η=1+F0−−√1−F0−−√
c=v⋅h
g=η2+c2−1−−−−−−−−−√
FCook−Torrance(v,h)=12(g−cg+c)2(1+((g+c)c−1(g−c)c+1)2)


Optimize
Be sure to optimize the BRDF shader code as a whole. I choose these forms of the equations to either match the literature or to demonstrate some property. They are not in the optimal form to compute in a pixel shader. For example, grouping Smith GGX with the BRDF denominator we have this:
GGGX(l)GGGX(v)4(n⋅l)(n⋅v)
In optimized HLSL it looks like this:

float a2 = a*a;
float G_V = NoV + sqrt( (NoV - NoV * a2) * NoV + a2 );
float G_L = NoL + sqrt( (NoL - NoL * a2) * NoL + a2 );
return rcp( G_V * G_L );

If you are using this on an older non-scalar GPU you could vectorize it as well.

References
[1] Hoffman 2013, "Background: Physics and Math of Shading"
[2] Blinn 1977, "Models of light reflection for computer synthesized pictures"
[3] Beckmann 1963, "The scattering of electromagnetic waves from rough surfaces"
[4] Walter et al. 2007, "Microfacet models for refraction through rough surfaces"
[5] Burley 2012, "Physically-Based Shading at Disney"
[6] Neumann et al. 1999, "Compact metallic reflectance models"
[7] Kelemen 2001, "A microfacet based coupled specular-matte brdf model with importance sampling"
[8] Smith 1967, "Geometrical shadowing of a random rough surface"
[9] Schlick 1994, "An Inexpensive BRDF Model for Physically-Based Rendering"
[10] Karis 2013, "Real Shading in Unreal Engine 4"
[11] Cook and Torrance 1982, "A Reflectance Model for Computer Graphics"
[12] Reed 2013, "How Is the NDF Really Defined?"















