#include "path.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void splitPath(char *fullPath, char **path, char **nomeArq, char **extArq)
{
    if (*path != NULL)
    {
        free(*path);
        *path = NULL;
    }
    if (*nomeArq != NULL)
    {
        free(*nomeArq);
        *nomeArq = NULL;
    }
    if (*extArq != NULL)
    {
        free(*extArq);
        *extArq = NULL;
    }
    char *ultimabarra = strrchr(fullPath, '/');
    if (ultimabarra == NULL)
    {
        *path = strdup("");
    }
    else
    {
        int tamanhoPath = strlen(fullPath) - strlen(ultimabarra) + 1;
        *path = malloc(tamanhoPath);
        strncpy(*path, fullPath, tamanhoPath);
        (*path)[tamanhoPath - 1] = '\0';
    }
    char *ultimoponto = strrchr(fullPath, '.');
    if (ultimoponto == NULL)
    {
        *extArq = strdup("");
        if (ultimabarra == NULL)
        {
            *nomeArq = malloc(strlen(fullPath) + 1);
            strcpy(*nomeArq, fullPath);
        }
        else
        {
            *nomeArq = malloc(strlen(ultimabarra) + 1);
            strncpy(*nomeArq, ultimabarra + 1, strlen(fullPath) - (ultimabarra - fullPath) - 1);
            (*nomeArq)[strlen(ultimabarra) - 1] = '\0';
        }
    }
    else
    {
        if (ultimabarra == NULL)
        {
            *nomeArq = malloc(strlen(fullPath) - strlen(ultimoponto) + 1);
            strncpy(*nomeArq, fullPath, strlen(fullPath) - strlen(ultimoponto));
            (*nomeArq)[strlen(fullPath) - strlen(ultimoponto)] = '\0';
            *extArq = malloc(strlen(ultimoponto) + 1);
            strcpy(*extArq, ultimoponto);
        }
        else
        {
            *nomeArq = malloc(strlen(ultimabarra) - strlen(ultimoponto) + 1);
            strncpy(*nomeArq, ultimabarra + 1, strlen(ultimabarra) - strlen(ultimoponto));
            (*nomeArq)[strlen(ultimoponto) - 1] = '\0';
            *extArq = malloc(strlen(ultimoponto) + 2);
            strcpy(*extArq, ultimoponto);
        }
    }
}

void joinFilePath(char *path, char *fileName, char **fullPath)
{
    if (path == NULL || fileName == NULL)
    {
        return;
    }
    if (*fullPath != NULL)
    {
        free(*fullPath);
        *fullPath = NULL;
    }

    if (strcmp("", path) != 0)
    {
        if (path[strlen(path) - 1] == '/')
        {
            *fullPath = malloc(strlen(path) + strlen(fileName) + 1);
            sprintf(*fullPath, "%s%s", path, fileName);
        }
        else
        {
            *fullPath = malloc(strlen(path) + strlen(fileName) + 2);
            sprintf(*fullPath, "%s/%s", path, fileName);
        }
    }
    else
    {
        *fullPath = malloc(strlen(fileName) + 1);
        sprintf(*fullPath, "%s", fileName);
    }
}

void joinAll(char *path, char *fileName, char *ext, char **fullPath)
{
    if (path == NULL || ext == NULL || fileName == NULL)
    {
        return;
    }
    if (*fullPath != NULL)
    {
        free(*fullPath);
        *fullPath = NULL;
    }
    if (strcmp("", path) != 0)
    {
        if (path[strlen(path) - 1] == '/')
        {
            *fullPath = malloc(strlen(path) + strlen(fileName) + strlen(ext) + 1);
            sprintf(*fullPath, "%s%s%s", path, fileName, ext);
        }
        else
        {
            *fullPath = malloc(strlen(path) + strlen(fileName) + strlen(ext) + 2);
            sprintf(*fullPath, "%s/%s%s", path, fileName, ext);
        }
    }
    else
    {
        *fullPath = malloc(strlen(fileName) + strlen(ext) + 1);
        sprintf(*fullPath, "%s%s", fileName, ext);
    }
}

void getFileName(char *fullPath, char **fileName)
{
    if (fullPath == NULL)
    {
        return;
    }
    if (*fileName != NULL)
    {
        free(*fileName);
        *fileName = NULL;
    }
    char *ultimabarra = strrchr(fullPath, '/');
    if (ultimabarra == NULL)
    {
        *fileName = strdup(fullPath);
    }
    else
    {
        *fileName = strdup(ultimabarra + 1);
    }
}

void getPath(char *fullPath, char **path)
{
    if (fullPath == NULL)
    {
        return;
    }
    if (*path != NULL)
    {
        free(*path);
        *path = NULL;
    }
    char *ultimabarra = strrchr(fullPath, '/');
    if (ultimabarra == NULL)
    {
        *path = strdup("");
    }
    else
    {
        int pathLength = ultimabarra - fullPath;
        *path = (char *)malloc((pathLength + 1) * sizeof(char));
        strncpy(*path, fullPath, pathLength);
        (*path)[pathLength] = '\0';
    }
}

void normalizePath(char *path, char **normPath)
{
    if (path == NULL)
    {
        return;
    }
    if (*normPath != NULL)
    {
        free(*normPath);
        *normPath = NULL;
    }
    int pathLength = strlen(path);
    if (path[pathLength - 1] == '/')
    {
        pathLength--;
    }
    *normPath = (char *)malloc((pathLength + 1) * sizeof(char));
    strncpy(*normPath, path, pathLength);
    (*normPath)[pathLength] = '\0';
}
