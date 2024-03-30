#include "Scene.hpp"
#include "./Materials/simplematerial.hpp"
#include "./Materials/simplerefractive.hpp"
#include "./Textures/checker.hpp"
#include "./Textures/image.hpp"
#include "./Textures/gradient.hpp"
#include "./Textures/basicvalnoise.hpp"
#include "./Textures/basicnoise.hpp"
#include "./Textures/marble.hpp"
#include "./Textures/qbStone1.hpp"
#include <chrono>

using namespace std;

qbRT::Scene::Scene()
{
	// **************************************************************************************
	// Configure the camera.
	// **************************************************************************************	
	m_camera.SetPosition(	qbVector3<double>{std::vector<double> {6.0, -10.0, -4.0}} );
	//m_camera.SetPosition( qbVector3<double>{std::vector<double> {-3.0, -5.0, -2.0}});
	m_camera.SetLookAt	( qbVector3<double>{std::vector<double> {0.0, 0.0, 0.5}} );
	m_camera.SetUp			( qbVector3<double>{std::vector<double> {0.0, 0.0, 1.0}} );
	m_camera.SetHorzSize(1.0);
	m_camera.SetLength(3.0);
	m_camera.SetAspect(16.0 / 9.0);
	m_camera.UpdateCameraGeometry();	
	
	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************		
	qbRT::MaterialBase::m_ambientColor = std::vector<double>{1.0, 1.0, 1.0};
	qbRT::MaterialBase::m_ambientIntensity = 0.25;

	// **************************************************************************************
	// Create the color maps.
	// **************************************************************************************	
	auto woodMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	woodMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});
	woodMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{100.0/255.0, 50.0/255.0, 30.0/255.0, 1.0}});
	woodMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 1.0}});	
	
	auto noiseMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	noiseMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 0.75, 0.0, 0.5}});
	noiseMap -> SetStop(0.5, qbVector4<double>{std::vector<double>{0.25, 0.25, 0.25, 0.25}});
	noiseMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.0, 0.0, 0.0, 0.0}});

	auto fineMap = std::make_shared<qbRT::Texture::ColorMap> (qbRT::Texture::ColorMap());
	fineMap -> SetStop(0.0, qbVector4<double>{std::vector<double>{100.0/255.0, 50.0/255.0, 30.0/255.0, 0.25}});
	fineMap -> SetStop(0.2, qbVector4<double>{std::vector<double>{200.0/255.0, 150.0/255.0, 120.0/255.0, 0.25}});
	fineMap -> SetStop(0.4, qbVector4<double>{std::vector<double>{0.0, 0.0, 0.0, 0.25}});
	fineMap -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.0, 0.0, 0.0, 0.0}});	

	// **************************************************************************************
	// Create the textures.
	// **************************************************************************************	
	auto Texture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	Texture -> LoadImage("C:/git/pic-bmp/7593526.bmp");
	Texture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );

	auto sphereTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	sphereTexture -> LoadImage("C:/git/pic-bmp/tennis_sph.bmp");
	sphereTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );
	
	auto torusTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	torusTexture -> LoadImage("C:/git/pic-bmp/4231186.bmp");
	torusTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );
						
	// The box image texture.										
	auto boxTexture = std::make_shared<qbRT::Texture::Image> (qbRT::Texture::Image());
	boxTexture -> LoadImage("C:/git/pic-bmp/WoodBoxTexture.bmp");
	boxTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{1.0, 1.0}} );																
	
	// The floor texture.
	auto floorTexture = std::make_shared<qbRT::Texture::Checker> (qbRT::Texture::Checker());
	floorTexture -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																0.0,
																qbVector2<double>{std::vector<double>{8.0, 8.0}} );
	floorTexture -> SetColor(qbVector4<double>{std::vector<double>{0.2, 0.2, 0.2, 1.0}}, qbVector4<double>{std::vector<double>{0.4, 0.4, 0.4, 1.0}});
	
	// Textures for the wooden torus.
	auto qbWood = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	qbWood -> SetColorMap(woodMap);
	qbWood -> SetAmplitude(8.0, 1.0);
	qbWood -> SetScale(2.0, 10.0);
	qbWood -> SetSine(1.0, 8.0);
	qbWood -> SetMinMax(-1.0, 1.0);
	qbWood -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});	
	
	auto dirtTexture1 = std::make_shared<qbRT::Texture::BasicValNoise> (qbRT::Texture::BasicValNoise());
	dirtTexture1 -> SetColorMap(noiseMap);
	dirtTexture1 -> SetAmplitude(2.0);
	dirtTexture1 -> SetScale(16.0);
	
	auto vertGrad1 = std::make_shared<qbRT::Texture::Gradient> (qbRT::Texture::Gradient());
	vertGrad1 -> SetStop(0.0, qbVector4<double>{std::vector<double>{1.0, 0.75, 0.0, 1.0}});
	vertGrad1 -> SetStop(0.5, qbVector4<double>{std::vector<double>{0.5, 0.5, 0.5, 0.25}});
	vertGrad1 -> SetStop(1.0, qbVector4<double>{std::vector<double>{0.5, 0.5, 0.5, 0.0}});
	vertGrad1 -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});
											
	auto fineTexture = std::make_shared<qbRT::Texture::Marble> (qbRT::Texture::Marble());
	fineTexture -> SetColorMap(fineMap);
	fineTexture -> SetAmplitude(2.0, 1.0);
	fineTexture -> SetScale(20.0, 40.0);
	fineTexture -> SetSine(64.0, 128.0);
	fineTexture -> SetMinMax(-1.0, 1.0);
	fineTexture -> SetTransform(qbVector2<double>{std::vector<double>{0.0, 0.0}}, 0.0, qbVector2<double>{std::vector<double>{1.0, 1.0}});			
	
	// **************************************************************************************
	// Create and setup normal maps.
	// **************************************************************************************
	auto woodBoxNormal = std::make_shared<qbRT::Normal::Image> (qbRT::Normal::Image());
	woodBoxNormal -> LoadImage("C:/git/pic-bmp/WoodBoxNormal.bmp");
	woodBoxNormal -> SetTransform(	qbVector2<double>{std::vector<double>{0.0, 0.0}},
																	0.0,
																	qbVector2<double>{std::vector<double>{1.0, 1.0}} );
																	
	auto woodNorm1 = std::make_shared<qbRT::Normal::TextureNormal> (qbRT::Normal::TextureNormal());
	woodNorm1 -> AssignBaseTexture(qbWood);
	woodNorm1 -> m_scale = 0.0001;
	
	auto fineNorm1 = std::make_shared<qbRT::Normal::TextureNormal> (qbRT::Normal::TextureNormal());
	fineNorm1 -> AssignBaseTexture(fineTexture);
	fineNorm1 -> m_scale = 0.001;
	fineNorm1 -> m_reverse = false;				
	
	auto mirrorNorm = std::make_shared<qbRT::Normal::SimpleRough> (qbRT::Normal::SimpleRough());	
	mirrorNorm -> m_amplitudeScale = 0.01;										

	// **************************************************************************************
	// Create some materials.
	// **************************************************************************************
	auto floorMaterial = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());	
	//floorMaterial -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	floorMaterial -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	floorMaterial -> m_reflectivity = 0.25;
	floorMaterial -> m_shininess = 0.0;
	floorMaterial -> AssignTexture(floorTexture);
	
	auto BodyMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//BodyMat -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	BodyMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	BodyMat -> m_reflectivity = 0.1;
	BodyMat -> m_shininess = 16.0;;
	BodyMat -> AssignTexture(Texture);

	auto sphereBodyMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//sphereBodyMat -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	sphereBodyMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	sphereBodyMat -> m_reflectivity = 0.1;
	sphereBodyMat -> m_shininess = 16.0;;
	sphereBodyMat -> AssignTexture(sphereTexture);

	auto torusBodyMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//torusBodyMat -> m_baseColor = qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}};
	torusBodyMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	torusBodyMat -> m_reflectivity = 0.1;
	torusBodyMat -> m_shininess = 16.0;;
	torusBodyMat -> AssignTexture(torusTexture);
	
	auto metalMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//metalMat -> m_baseColor = qbVector3<double>{std::vector<double>{0.3, 0.3, 0.3}};
	metalMat -> m_baseColor = std::vector<double>{0.3, 0.3, 0.3};
	metalMat -> m_reflectivity = 0.5;
	metalMat -> m_shininess = 64.0;
	
	auto plasticMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	//plasticMat -> m_baseColor = qbVector3<double>{std::vector<double>{0.75, 0.75, 0.75}};
	plasticMat -> m_baseColor = std::vector<double>{0.75, 0.75, 0.75};
	plasticMat -> m_reflectivity = 0.0;
	plasticMat -> m_shininess = 0.0;
	
	auto mirrorMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	mirrorMat -> m_baseColor = std::vector<double>{0.0, 0.0, 1.0};
	mirrorMat -> m_reflectivity = 0.5;
	mirrorMat -> m_shininess = 64.0;
	mirrorMat -> AssignNormalMap(mirrorNorm);
	
	auto mirrorMat2 = std::make_shared<qbRT::SimpleMaterial> (*mirrorMat);
	mirrorMat2 -> m_baseColor = std::vector<double>{1.0, 1.0, 0.0};
	
	auto boxMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	boxMat -> m_baseColor = std::vector<double>{1.0, 1.0, 0.0};
	boxMat -> m_reflectivity = 0.0;
	boxMat -> m_shininess = 32.0;
	boxMat -> AssignTexture(boxTexture);
	boxMat -> AssignNormalMap(woodBoxNormal);
	
	auto woodMat = std::make_shared<qbRT::SimpleMaterial> (qbRT::SimpleMaterial());
	woodMat -> m_baseColor = std::vector<double>{1.0, 1.0, 1.0};
	woodMat -> m_reflectivity = 0.0;
	woodMat -> m_shininess = 32.0;
	woodMat -> AssignTexture(qbWood);
	woodMat -> AssignTexture(fineTexture);
	woodMat -> AssignTexture(dirtTexture1);
	woodMat -> AssignTexture(vertGrad1);
	woodMat -> AssignNormalMap(woodNorm1);
	woodMat -> AssignNormalMap(fineNorm1);		
	
	// **************************************************************************************	
	// Create and setup objects.
	// **************************************************************************************
	auto floor = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	floor -> m_tag = "floor";
	floor -> m_isVisible = true;
	floor -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{0.0, 0.0, 0.5}},
												qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
												qbVector3<double>{std::vector<double>{6.0, 6.0, 1.0}}}	);	
	floor -> AssignMaterial(floorMaterial);	
	floor -> m_uvMapType = qbRT::uvPLANE;
	
	auto backWall = std::make_shared<qbRT::ObjPlane> (qbRT::ObjPlane());
	backWall -> m_tag = "backWall";
	backWall -> m_isVisible = true;
	backWall -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{0.0, 2.0, 0.0}},
													qbVector3<double>{std::vector<double>{-M_PI/2.0, 0.0, 0.0}},
													qbVector3<double>{std::vector<double>{4.0, 4.0, 1.0}}}	);	
	backWall -> AssignMaterial(mirrorMat);
	
	auto sideWall = std::make_shared<qbRT::ObjPlane> (*backWall);
	sideWall -> m_tag = "sideWall";
	sideWall -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{-2.0, 0.0, 0.0}},
													qbVector3<double>{std::vector<double>{-M_PI/2.0, -M_PI/2.0, 0.0}},
													qbVector3<double>{std::vector<double>{4.0, 4.0, 1.0}}}	);	
	sideWall -> AssignMaterial(mirrorMat2);
	
	//double sprayX = 1.0;
	//double sprayY = -1.5;	
	double sprayX = 0.0;
	double sprayY = 0.0;
	auto penBody = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	penBody -> m_tag = "penBody";
	penBody -> m_isVisible = true;
	penBody -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{sprayX, sprayY, -0.5}},
												qbVector3<double>{std::vector<double>{0.0, 0.0, M_PI/5.0}},
												qbVector3<double>{std::vector<double>{0.1, 0.1, 1.0}}});
	penBody -> AssignMaterial(BodyMat);
	penBody -> m_uvMapType = qbRT::uvCYLINDER;
	
	auto penTopCone = std::make_shared<qbRT::Cone> (qbRT::Cone());
	penTopCone -> m_tag = "penTopCone";
	penTopCone -> m_isVisible = true;
	penTopCone -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{sprayX, sprayY, -2.0}},
												   qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
												   qbVector3<double>{std::vector<double>{0.03, 0.03, 0.11}}});
	penTopCone -> AssignMaterial(metalMat);
	
	auto penTop = std::make_shared<qbRT::Cone> (*penTopCone);
	penTop -> m_tag = "penTop";
	penTop -> m_isVisible = true;
	penTop -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{sprayX, sprayY, -2.0}},
											   qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
											   qbVector3<double>{std::vector<double>{0.1, 0.1, 0.5}}});
	penTop -> AssignMaterial(plasticMat);

	/*double sprayX = 0.0;
	double sprayY = 0.0;
	auto sprayBody = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	sprayBody -> m_tag = "sprayBody";
	sprayBody -> m_isVisible = true;
	sprayBody -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{sprayX, sprayY, -0.5}},
																									qbVector3<double>{std::vector<double>{0.0, 0.0, M_PI/5.0}},
																									qbVector3<double>{std::vector<double>{0.4, 0.4, 1.0}}}	);
	sprayBody -> AssignMaterial(BodyMat);
	sprayBody -> m_uvMapType = qbRT::uvCYLINDER;
	
	auto sprayTopCone = std::make_shared<qbRT::Cone> (qbRT::Cone());
	sprayTopCone -> m_tag = "sprayTopCone";
	sprayTopCone -> m_isVisible = true;
	sprayTopCone -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{sprayX, sprayY, -2.0}},
																										qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																										qbVector3<double>{std::vector<double>{0.4, 0.4, 0.5}}}	);
	sprayTopCone -> AssignMaterial(metalMat);
	
	auto sprayTop = std::make_shared<qbRT::Cylinder> (qbRT::Cylinder());
	sprayTop -> m_tag = "sprayTop";
	sprayTop -> m_isVisible = true;
	sprayTop -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{sprayX, sprayY, -1.5}},
																								qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
																								qbVector3<double>{std::vector<double>{0.2, 0.2, 0.5}}}	);
	sprayTop -> AssignMaterial(plasticMat);*/

	auto pen = std::make_shared<qbRT::SHAPES::CompositeBase> (qbRT::SHAPES::CompositeBase());
	pen -> m_tag = "pen";
	pen -> m_isVisible = true;
	//pen -> AddSubShape(sprayBody);
	//pen -> AddSubShape(sprayTopCone);
	//pen -> AddSubShape(sprayTop);
	pen -> AddSubShape(penBody);
	pen -> AddSubShape(penTopCone);
	pen -> AddSubShape(penTop);
	pen -> SetTransformMatrix(qbRT::GTform{qbVector3<double>{std::vector<double>{1.0, -1.75, 0.0}},
	                                       qbVector3<double>{std::vector<double>{0.0, -M_PI/4.0, 0.0}},
										   qbVector3<double>{std::vector<double>{1.0, 1.0, 1.0}}});

	//penBody -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{sprayX, sprayY, -0.5}},
	//											qbVector3<double>{std::vector<double>{0.0, 0.0, M_PI/5.0}},
	//											qbVector3<double>{std::vector<double>{0.1, 0.1, 1.0}}});
	
	auto box = std::make_shared<qbRT::Box> (qbRT::Box());
	box -> m_tag = "box";
	box -> m_isVisible = true;
	box -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{-1.0, -2.0, 0.1}},
											qbVector3<double>{std::vector<double>{0.0, 0.0, -M_PI/6.0}},
											qbVector3<double>{std::vector<double>{0.4, 0.4, 0.4}}}	);
	box -> AssignMaterial(boxMat);
	box -> m_uvMapType = qbRT::uvBOX;

	auto box2 = std::make_shared<qbRT::Box> (*box);
	box2 -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{-0.5, -1.1, 0.1}},
										     qbVector3<double>{std::vector<double>{0.0, 0.0, M_PI/3.0}},
											 qbVector3<double>{std::vector<double>{0.4, 0.4, 0.4}}});

	auto box3 = std::make_shared<qbRT::Box> (*box);
	box3 -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{-0.75, -1.5, -0.7}},
										     qbVector3<double>{std::vector<double>{0.0, 0.0, M_PI}},
											 qbVector3<double>{std::vector<double>{0.4, 0.4, 0.4}}});

    auto ball = std::make_shared<qbRT::RM::Sphere> (qbRT::RM::Sphere());
	ball -> m_isVisible = true;
	ball -> SetTransformMatrix(qbRT::GTform {qbVector3<double>{std::vector<double>{2.0, -1.0, -0.08}},
											   qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
											   qbVector3<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	ball -> AssignMaterial(sphereBodyMat);
	ball -> m_uvMapType = qbRT::uvSPHERE;

	auto donut = std::make_shared<qbRT::RM::Torus> (qbRT::RM::Torus());
	donut -> m_tag = "donut";
	donut -> m_isVisible = true;
	donut -> SetRadii(0.7, 0.3);
	donut -> SetTransformMatrix(qbRT::GTform {	qbVector3<double>{std::vector<double>{2.0, -3.0, 0.3}},
												qbVector3<double>{std::vector<double>{0.0, 0.0, 0.0}},
												qbVector3<double>{std::vector<double>{0.75, 0.75, 0.75}}});
	donut -> AssignMaterial(torusBodyMat);
	donut -> m_uvMapType = qbRT::uvSPHERE;

	// **************************************************************************************
	// Put the objects into the scene.	
	// **************************************************************************************
	//m_objectList.push_back(penBody);
	//m_objectList.push_back(penTopCone);
	//m_objectList.push_back(penTop);
	m_objectList.push_back(pen);
	m_objectList.push_back(box);
	m_objectList.push_back(box2);	
	m_objectList.push_back(box3);
	m_objectList.push_back(ball);
	m_objectList.push_back(floor);
	m_objectList.push_back(backWall);
	m_objectList.push_back(sideWall);
	m_objectList.push_back(donut);
	
	// **************************************************************************************	
	// Construct and setup the lights.
	// **************************************************************************************	
	auto leftLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	leftLight -> m_location = qbVector3<double> {std::vector<double> {0.0, -20.0, -20.0}};
	leftLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	leftLight -> m_intensity = 4.0;
	
	auto rightLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	rightLight -> m_location = qbVector3<double> {std::vector<double> {8.0, -20.0, -20.0}};
	rightLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	rightLight -> m_intensity = 6.0;
	
	auto topLight = std::make_shared<qbRT::PointLight> (qbRT::PointLight());
	topLight -> m_location = qbVector3<double> {std::vector<double> {0.0, 3.0, -20.0}};
	topLight -> m_color = qbVector3<double> {std::vector<double> {1.0, 1.0, 1.0}};
	topLight -> m_intensity = 1.0;
	
	m_lightList.push_back(leftLight);
	m_lightList.push_back(rightLight);
	m_lightList.push_back(topLight);

}

// Function to perform the rendering.
bool qbRT::Scene::Render(qbImage &outputImage)
{
	// Record the start time.
	auto startTime = std::chrono::steady_clock::now();

	// Get the dimensions of the output image.
	int xSize = outputImage.GetXSize();
	int ySize = outputImage.GetYSize();
	
	// Loop over each pixel in our image.
	qbRT::Ray cameraRay;
	qbVector3<double> intPoint			(3);
	qbVector3<double> localNormal	(3);
	qbVector3<double> localColor		(3);
	double xFact = 1.0 / (static_cast<double>(xSize) / 2.0);
	double yFact = 1.0 / (static_cast<double>(ySize) / 2.0);
	double minDist = 1e6;
	double maxDist = 0.0;
	for (int y=0; y<ySize; ++y)
	{
		// Display progress.
		std::cout << "Processing line " << y << " of " << ySize << "." << " \r";
		std::cout.flush();
		
		for (int x=0; x<xSize; ++x)
		{
			// Normalize the x and y coordinates.
			double normX = (static_cast<double>(x) * xFact) - 1.0;
			double normY = (static_cast<double>(y) * yFact) - 1.0;
			
			// Generate the ray for this pixel.
			m_camera.GenerateRay(normX, normY, cameraRay);
			
			// Test for intersections with all objects in the Scene_E21.
			std::shared_ptr<qbRT::ObjectBase> closestObject;
			qbVector3<double> closestIntPoint		{3};
			qbVector3<double> closestLocalNormal	{3};
			qbVector3<double> closestLocalColor	{3};
			qbRT::DATA::hitData closestHitData;
			bool intersectionFound = CastRay(cameraRay, closestObject, closestHitData);
			
			/* Compute the illumination for the closest object, assuming that there
				was a valid intersection. */
			if (intersectionFound)
			{
				// Check if the object has a material.
				if (closestHitData.hitObject -> m_hasMaterial)
				{
					// Use the material to compute the color.
					qbRT::MaterialBase::m_reflectionRayCount = 0;
					qbVector3<double> color = closestHitData.hitObject -> m_pMaterial -> ComputeColor(	m_objectList, m_lightList,
																																														closestHitData.hitObject, closestHitData.poi,
																																														closestHitData.normal, cameraRay);
					outputImage.SetPixel(x, y, color.GetElement(0), color.GetElement(1), color.GetElement(2));
				}
				else
				{
					// Use the basic method to compute the color.
					qbVector3<double> matColor = qbRT::MaterialBase::ComputeDiffuseColor(m_objectList, m_lightList,
																																							closestHitData.hitObject, closestHitData.poi,
																																							closestHitData.normal, closestObject->m_baseColor);
					outputImage.SetPixel(x, y, matColor.GetElement(0), matColor.GetElement(1), matColor.GetElement(2));
				}
			}
		}
	}
	
	// Record the end time.
	auto endTime = std::chrono::steady_clock::now();
    
	// Compute the time it took to render.
	std::chrono::duration<double> renderTime = endTime - startTime;
	std::cout.flush();
	std::cout << "\n\nRendering time: " << renderTime.count() << "s" << std::endl;

	std::cout << std::endl;
	return true;
}

// Function to cast a ray into the scene.
bool qbRT::Scene::CastRay(	qbRT::Ray &castRay, std::shared_ptr<qbRT::ObjectBase> &closestObject,
														qbRT::DATA::hitData &closestHitData)
{
	qbRT::DATA::hitData hitData;
	double minDist = 1e6;
	bool intersectionFound = false;
	for (auto currentObject : m_objectList)
	{
		bool validInt = currentObject -> TestIntersection(castRay, hitData);
		
		// If we have a valid intersection.
		if (validInt)
		{
			// Set the flag to indicate that we found an intersection.
			intersectionFound = true;
					
			// Compute the distance between the camera and the point of intersection.
			double dist = (hitData.poi - castRay.m_point1).norm();
					
			/* If this object is closer to the camera than any one that we have
				seen before, then store a reference to it. */
			if (dist < minDist)
			{
				minDist = dist;
				closestObject = currentObject;
				//closestIntPoint = intPoint;
				//closestLocalNormal = localNormal;
				//closestLocalColor = localColor;
				closestHitData = hitData;
			}
		}
	}
	
	return intersectionFound;
}
