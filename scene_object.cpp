#include <cmath>
#include <iostream>
#include "scene_object.h"
#include <math.h>

bool UnitSquare::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
                const Matrix4x4& modelToWorld ) {
        // TODO: implement intersection code for UnitSquare, which is
        // defined on the xy-plane, with vertices (0.5, 0.5, 0), 
        // (-0.5, 0.5, 0), (-0.5, -0.5, 0), (0.5, -0.5, 0), and normal
        // (0, 0, 1).
        //
        // Your goal here is to fill ray.intersection with correct values
        // should an intersection occur.  This includes intersection.point, 
        // intersection.normal, intersection.none, intersection.t_value.   
        //
        // HINT: Remember to first transform the ray into object space  
        // to simplify the intersection test.
        
        //Transform ray to object space
        Ray3D rayObjectSpace = Ray3D(worldToModel * ray.origin, worldToModel * ray.dir);        
        //point = ray.origin + t_value * ray.origin
        //point for unitsquare is (0, 0, 0)
        double t_value = -rayObjectSpace.origin[2] / rayObjectSpace.dir[2];
        if(t_value <= 0) {
        	return false;
        }
        
        
        Point3D intersectionpoint = rayObjectSpace.origin + t_value * rayObjectSpace.dir;
        bool intersection = false;
        
        if(intersectionpoint[0] > 0.5 || intersectionpoint[0] < -0.5 || intersectionpoint[1] > 0.5 || intersectionpoint[1] < -0.5) {
        	return false;
        }
        
        if(ray.intersection.none || t_value < ray.intersection.t_value){
                intersection = true;
                ray.intersection.point = modelToWorld * intersectionpoint;
                ray.intersection.normal = worldToModel.transpose()*Vector3D(0, 0, 1);
                ray.intersection.normal.normalize();
                ray.intersection.none = false;
                ray.intersection.t_value = t_value;
                return true;
        }
        
        return false;
}




bool UnitSphere::intersect( Ray3D& ray, const Matrix4x4& worldToModel,
                const Matrix4x4& modelToWorld ) {
        // TODO: implement intersection code for UnitSphere, which is centred 
        // on the origin.  
        //
        // Your goal here is to fill ray.intersection with correct values
        // should an intersection occur.  This includes intersection.point, 
        // intersection.normal, intersection.none, intersection.t_value.   
        //
        // HINT: Remember to first transform the ray into object space  
        // to simplify the intersection test.
        
        bool intersection = false;
        Ray3D rayObjectSpace = Ray3D(worldToModel * ray.origin, worldToModel * ray.dir);
        //unitSphere is radius of 1 and center at (0, 0, 0)
        double cx = rayObjectSpace.origin[0];
        double cy = rayObjectSpace.origin[1];
        double cz = rayObjectSpace.origin[2];
        double dx = rayObjectSpace.dir[0];
        double dy = rayObjectSpace.dir[1];
        double dz = rayObjectSpace.dir[2];
        
        double a = dx * dx + dy * dy + dz * dz;
        double b = 2 * dx * cx + 2 * dy * cy + 2 * dz * cz;
        double c = cx * cx + cy * cy + cz * cz - 1;
        
        double t_value;
        double discriminant = b * b - 4 * a * c;
        if(discriminant < 0){
                return intersection;
        }
        else{
                double root1 = (-1*b + sqrt(discriminant)) / (2 * a);
                double root2 = (-1*b - sqrt(discriminant)) / (2 * a);
                
                if (root1 > 0 && root2 > 0){
                		if(root1 < root2) t_value = root1;
                    	else t_value = root2;
                        intersection = true;
                }else if (root2 > 0 && root1 <= 0) {
                        t_value = root2;
                        intersection = true;
                }else if (root1 > 0 && root2 <= 0){
                        t_value = root1;
                        intersection = true;
                }else {
                		return intersection;
                }
        }

        Point3D intersectionPoint = rayObjectSpace.origin + t_value * rayObjectSpace.dir;
        
        if(ray.intersection.none || t_value < ray.intersection.t_value){
                intersection = true;
                ray.intersection.point = modelToWorld * intersectionPoint;
                ray.intersection.normal = worldToModel.transpose()*Vector3D(intersectionPoint[0], intersectionPoint[1], intersectionPoint[2]);
                ray.intersection.normal.normalize();
                ray.intersection.none = false;
                ray.intersection.t_value = t_value;
                
        }       
        return intersection;
}