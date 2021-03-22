//
// Created by Nikita Kruk on 08.03.20.
//

#ifndef SELFREPLICATINGCOLLOIDALCLUSTERSMOVIE_RENDERERFORSTATICTETRAHEDRONS_HPP
#define SELFREPLICATINGCOLLOIDALCLUSTERSMOVIE_RENDERERFORSTATICTETRAHEDRONS_HPP

#include "Definitions.hpp"
#include "Model.hpp"
#include "ScreenshotHandler.hpp"

#include <string>
#include <vector>
#include <array>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include <ft2build.h>
#include FT_FREETYPE_H

class RendererForStaticTetrahedrons
{
 public:

  RendererForStaticTetrahedrons(Model *model);
  ~RendererForStaticTetrahedrons();

  void Start();

 private:

  ScreenshotHandler screenshot_handler_;
  Model *model_;

  static bool stop_flag_;
  static bool pause_flag_;
  static bool take_screenshot_flag_;
  static int frame_speed_; // 1 - the basic frame rate
  static GLfloat x_rot_;
  static GLfloat y_rot_;
  static GLfloat z_rot_;
  static glm::vec3 camera_pos_;
  static glm::vec3 camera_front_;
  static glm::vec3 camera_up_;
  static glm::vec3 light_pos_;
  static float delta_time_;  // Time between current frame and last frame
  static float last_frame_; // Time of last frame
  static float last_x_;
  static float last_y_;
  static GLfloat yaw_;
  static GLfloat pitch_;
  static bool first_mouse_;
  static float fov_;
  static int screenshot_count_;
  static int t_start_;
  static bool show_time_;
  static Real time_stamp_to_show_;
  static int number_of_color_components_; // RGB | Alpha is implemented in the shaders
  static ParticleRepresentationType particle_representation_type_;
  FT_Library ft_; // FreeType library object
  FT_Face face_; // FreeType face object

  static float ambient_strength_;
  static float diffuse_strength_;
  static float specular_strength_;

//  std::vector<Real> colloidal_particles_;
//  std::vector<int> colloidal_particle_subtypes_;
  std::vector<std::vector<std::array<GLfloat, 3>>> sphere_template_;
  std::vector<std::vector<std::array<GLfloat, 3>>> sphere_normals_;

  static void ErrorCallback(int error, const char *description);
  static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
  void InitShaders(GLuint shader_program[]);
  static void SetShaderParameter(GLuint shader_program,
                                 GLfloat parameter_value,
                                 const std::string &parameter_name_in_shader);
  static void SetShaderParameter(GLuint shader_program,
                                 GLint parameter_value,
                                 const std::string &parameter_name_in_shader);
  void SetShaderParameter(GLuint shader_program,
                          const glm::vec3 &parameter_value,
                          const std::string &parameter_name_in_shader);
  static void FinFunc();
  void DefineSceneWithTetrahedronsOfDifferentMonomers();
  void DefineSceneWithOneParentTetrahedron();
  void DefineSceneWithReplicationOfOneTetrahedron();
  void DefineSceneWithHigherOrderReplication();
  void ReadNewState();
  void CreateTransformationMatrices(int width, int height, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection);
  void ImportTransformationMatrices(GLuint shader_program,
                                    const glm::mat4 &model,
                                    const glm::mat4 &view,
                                    const glm::mat4 &projection);
  void DisplayFunc(GLFWwindow *window, GLuint vao[], GLuint vbo[], GLuint shader_program[]);
  void RenderWiredBorder(GLuint vao, GLuint vbo, GLuint shader_program);
  void RenderSolidBorder(GLuint vao, GLuint vbo, GLuint shader_program, const glm::mat4 &model);
  void RenderColloidalParticles(GLuint vao, GLuint vbo, GLuint shader_program, const glm::mat4 &model);
  void ComposeSphereTemplate(float radius);
  void RenderText(const std::string &text,
                  GLfloat x,
                  GLfloat y,
                  GLfloat sx,
                  GLfloat sy,
                  GLuint vao,
                  GLuint vbo,
                  GLuint shader_program);
  static void ReadShaderSource(const std::string &fname, std::vector<char> &buffer);
  static GLuint LoadAndCompileShader(const std::string &fname, GLenum shader_type);
  static GLuint CreateProgramFromShader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);
  static GLuint CreateProgramFromShader(const std::string &vertex_shader_path,
                                        const std::string &geometry_shader_path,
                                        const std::string &fragment_shader_path);

  void AddNewTetrahedron(const glm::mat4 &rotate,
                         const glm::mat4 &translate,
                         int number_of_parent_colloidal_particles,
                         const std::vector<glm::vec3> &tetrahedral_colloids_in_local_frame,
                         const glm::vec3 &center_of_mass,
                         const std::vector<int> &colloidal_particle_subtypes);
  void AddNewComplementaryTetrahedron(const glm::mat4 &rotate,
                                      const glm::mat4 &translate,
                                      int number_of_parent_colloidal_particles,
                                      const std::vector<glm::vec3> &tetrahedral_colloids_in_local_frame,
                                      const glm::vec3 &center_of_mass,
                                      const std::vector<int> &colloidal_particle_subtypes);
  void AddNewManualTetrahedron(const glm::mat4 &rotate,
                               const glm::mat4 &translate,
                               int number_of_parent_colloidal_particles,
                               const std::vector<glm::vec3> &tetrahedral_colloids_in_local_frame,
                               const glm::vec3 &center_of_mass,
                               const std::vector<int> &manual_subtypes);
  void AddNewColloids(int number_of_parent_colloidal_particles, int seed = 0);

};

#endif //SELFREPLICATINGCOLLOIDALCLUSTERSMOVIE_RENDERERFORSTATICTETRAHEDRONS_HPP
