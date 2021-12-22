name := "Scala-Applied-Exercises"

version in ThisBuild := "1.0-SNAPSHOT"

scalaVersion in ThisBuild := "2.12.4"

scalacOptions in ThisBuild += "-deprecation"

libraryDependencies in ThisBuild ++= Seq(
  "org.scalactic"  %% "scalactic"  % "3.0.4",
  "org.scalatest"  %% "scalatest"  % "3.0.4"  % Test,
  "org.scalamock"  %% "scalamock"  % "4.1.0"  % Test,
  "org.scalacheck" %% "scalacheck" % "1.13.4" % Test
)

lazy val module01 = project
lazy val module02 = project
lazy val module03 = project
lazy val module04 = project
lazy val module05 = project
lazy val module06 = project
