/*=========================================================================

  Library:   CTK

  Copyright (c) PerkLab 2013

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0.txt

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMDisplayedFieldGeneratorDefaultRule_h
#define __ctkDICOMDisplayedFieldGeneratorDefaultRule_h

// Qt includes
#include <QStringList>

#include "ctkDICOMDisplayedFieldGeneratorAbstractRule.h"

#define EMPTY_SERIES_DESCRIPTION "Unnamed Series"

/// \ingroup DICOM_Core
///
/// Default rule for generating displayed fields from DICOM fields
class CTK_DICOM_CORE_EXPORT ctkDICOMDisplayedFieldGeneratorDefaultRule : public ctkDICOMDisplayedFieldGeneratorAbstractRule
{
public: 
  virtual EvaluationResult evaluate(QStringList dicomFields, QMap<QString, QString> displayedFields, const ctkDICOMDatabase &db)
  {
    // TODO: fill default patient, study, series tables
    // Patient:PatientID, Patient:PatientName
    return RULE_APPLIED_CONTINUE_PROCESSING;
  }

  virtual QStringList getRequiredDICOMTags()
  {
    QStringList requiredTags;

    requiredTags << dicomTagToString(DCM_SOPInstanceUID);

    requiredTags << dicomTagToString(DCM_PatientID);
    requiredTags << dicomTagToString(DCM_PatientName);
    requiredTags << dicomTagToString(DCM_PatientBirthDate);
    requiredTags << dicomTagToString(DCM_PatientBirthTime);
    requiredTags << dicomTagToString(DCM_PatientSex);
    requiredTags << dicomTagToString(DCM_PatientAge);
    requiredTags << dicomTagToString(DCM_PatientComments);

    requiredTags << dicomTagToString(DCM_StudyInstanceUID);
    requiredTags << dicomTagToString(DCM_StudyID);
    requiredTags << dicomTagToString(DCM_StudyDate);
    requiredTags << dicomTagToString(DCM_StudyTime);
    requiredTags << dicomTagToString(DCM_AccessionNumber);
    requiredTags << dicomTagToString(DCM_ModalitiesInStudy);
    requiredTags << dicomTagToString(DCM_InstitutionName);
    requiredTags << dicomTagToString(DCM_PerformingPhysicianName);
    requiredTags << dicomTagToString(DCM_ReferringPhysicianName);
    requiredTags << dicomTagToString(DCM_StudyDescription);

    requiredTags << dicomTagToString(DCM_SeriesInstanceUID);
    requiredTags << dicomTagToString(DCM_SeriesDate);
    requiredTags << dicomTagToString(DCM_SeriesTime);
    requiredTags << dicomTagToString(DCM_SeriesDescription);
    requiredTags << dicomTagToString(DCM_Modality);
    requiredTags << dicomTagToString(DCM_BodyPartExamined);
    requiredTags << dicomTagToString(DCM_FrameOfReferenceUID);
    requiredTags << dicomTagToString(DCM_ContrastBolusAgent);
    requiredTags << dicomTagToString(DCM_ScanningSequence);
    requiredTags << dicomTagToString(DCM_SeriesNumber);
    requiredTags << dicomTagToString(DCM_AcquisitionNumber);
    requiredTags << dicomTagToString(DCM_EchoNumbers);
    requiredTags << dicomTagToString(DCM_TemporalPositionIdentifier);   

    return requiredTags;
  }

  virtual void registerEmptyFieldNames(QMap<QString, QString> emptyFieldNamesDisplayPatients, QMap<QString, QString> emptyFieldNamesDisplayStudies, QMap<QString, QString> emptyFieldNamesDisplaySeries)
  {
    emptyFieldNamesDisplaySeries.insertMulti("SeriesDescription", EMPTY_SERIES_DESCRIPTION);
  }

  virtual void getDisplayFieldsForInstance(QMap<QString, QString> cachedTags, QMap<QString, QString> &displayFieldsForCurrentSeries, QMap<QString, QString> &displayFieldsForCurrentStudy, QMap<QString, QString> &displayFieldsForCurrentPatient)
  {
    displayFieldsForCurrentPatient["PatientName"]=cachedTags[dicomTagToString(DCM_PatientName)];    
    displayFieldsForCurrentPatient.insert("PatientID",cachedTags[dicomTagToString(DCM_PatientID)]);

    displayFieldsForCurrentStudy.insert("StudyInstanceUID",cachedTags[dicomTagToString(DCM_StudyInstanceUID)]);
    displayFieldsForCurrentStudy.insert("StudyDescription",cachedTags[dicomTagToString(DCM_StudyDescription)]);
    displayFieldsForCurrentStudy.insert("StudyDate",cachedTags[dicomTagToString(DCM_StudyDate)]);
    displayFieldsForCurrentStudy.insert("ModalitiesInStudy",cachedTags[dicomTagToString(DCM_ModalitiesInStudy)]);
    displayFieldsForCurrentStudy.insert("InstitutionName",cachedTags[dicomTagToString(DCM_InstitutionName)]);
    displayFieldsForCurrentStudy.insert("ReferringPhysician",cachedTags[dicomTagToString(DCM_ReferringPhysicianName)]);

    displayFieldsForCurrentSeries.insert("SeriesInstanceUID",cachedTags[dicomTagToString(DCM_SeriesInstanceUID)]);
    displayFieldsForCurrentSeries.insert("StudyInstanceUID",cachedTags[dicomTagToString(DCM_StudyInstanceUID)]);
    displayFieldsForCurrentSeries.insert("SeriesNumber",cachedTags[dicomTagToString(DCM_SeriesNumber)]);
    displayFieldsForCurrentSeries.insert("SeriesDescription",cachedTags[dicomTagToString(DCM_SeriesDescription)]);
    displayFieldsForCurrentSeries.insert("Modality",cachedTags[dicomTagToString(DCM_Modality)]);
  }

  virtual void mergeDisplayFieldsForInstance(
    const QMap<QString, QString> &initialFieldsSeries, const QMap<QString, QString> &initialFieldsStudy, const QMap<QString, QString> &initialFieldsPatient,
    const QMap<QString, QString> &newFieldsSeries, const QMap<QString, QString> &newFieldsStudy, const QMap<QString, QString> &newFieldsPatient,
    QMap<QString, QString> &mergedFieldsSeries, QMap<QString, QString> &mergedFieldsStudy, QMap<QString, QString> &mergedFieldsPatient,
    const QMap<QString, QString> &emptyFieldNamesSeries, const QMap<QString, QString> &emptyFieldNamesStudy, const QMap<QString, QString> &emptyFieldNamesPatient
    )
  {

    // TODO: get the real empty fields list from somewhere
    QMap<QString, QString> emptyFieldsPatient;
    QMap<QString, QString> emptyFieldsStudy;
    QMap<QString, QString> emptyFieldsSeries;

    mergeExpectSameValue("PatientName", initialFieldsPatient, newFieldsPatient, mergedFieldsPatient, emptyFieldsPatient);
    mergeExpectSameValue("PatientID", initialFieldsPatient, newFieldsPatient, mergedFieldsPatient, emptyFieldsPatient);

    mergeConcatenate("StudyDescription", initialFieldsStudy, newFieldsStudy, mergedFieldsStudy, emptyFieldsStudy);
    mergeExpectSameValue("StudyDate", initialFieldsStudy, newFieldsStudy, mergedFieldsStudy, emptyFieldsStudy);
    mergeConcatenate("ModalitiesInStudy", initialFieldsStudy, newFieldsStudy, mergedFieldsStudy, emptyFieldsStudy);
    mergeExpectSameValue("InstitutionName", initialFieldsStudy, newFieldsStudy, mergedFieldsStudy, emptyFieldsStudy);
    mergeConcatenate("ReferringPhysician", initialFieldsStudy, newFieldsStudy, mergedFieldsStudy, emptyFieldsStudy);

    mergeExpectSameValue("SeriesNumber", initialFieldsSeries, newFieldsSeries, mergedFieldsSeries, emptyFieldsSeries);
    mergeConcatenate("SeriesDescription", initialFieldsSeries, newFieldsSeries, mergedFieldsSeries, emptyFieldsSeries);
    mergeExpectSameValue("Modality", initialFieldsSeries, newFieldsSeries, mergedFieldsSeries, emptyFieldsSeries);
  }

};

#endif